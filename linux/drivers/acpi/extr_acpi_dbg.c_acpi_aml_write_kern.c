#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct circ_buf {char* buf; size_t head; } ;
struct TYPE_2__ {struct circ_buf out_crc; } ;

/* Variables and functions */
 int ACPI_AML_BUF_SIZE ; 
 int /*<<< orphan*/  ACPI_AML_OUT_KERN ; 
 TYPE_1__ acpi_aml_io ; 
 int acpi_aml_lock_write (struct circ_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_aml_unlock_fifo (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  circ_space_to_end (struct circ_buf*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static int acpi_aml_write_kern(const char *buf, int len)
{
	int ret;
	struct circ_buf *crc = &acpi_aml_io.out_crc;
	int n;
	char *p;

	ret = acpi_aml_lock_write(crc, ACPI_AML_OUT_KERN);
	if (ret < 0)
		return ret;
	/* sync tail before inserting logs */
	smp_mb();
	p = &crc->buf[crc->head];
	n = min(len, circ_space_to_end(crc));
	memcpy(p, buf, n);
	/* sync head after inserting logs */
	smp_wmb();
	crc->head = (crc->head + n) & (ACPI_AML_BUF_SIZE - 1);
	acpi_aml_unlock_fifo(ACPI_AML_OUT_KERN, true);
	return n;
}