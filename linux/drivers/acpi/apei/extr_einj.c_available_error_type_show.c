#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int einj_get_available_error_type (int*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*) ; 

__attribute__((used)) static int available_error_type_show(struct seq_file *m, void *v)
{
	int rc;
	u32 available_error_type = 0;

	rc = einj_get_available_error_type(&available_error_type);
	if (rc)
		return rc;
	if (available_error_type & 0x0001)
		seq_printf(m, "0x00000001\tProcessor Correctable\n");
	if (available_error_type & 0x0002)
		seq_printf(m, "0x00000002\tProcessor Uncorrectable non-fatal\n");
	if (available_error_type & 0x0004)
		seq_printf(m, "0x00000004\tProcessor Uncorrectable fatal\n");
	if (available_error_type & 0x0008)
		seq_printf(m, "0x00000008\tMemory Correctable\n");
	if (available_error_type & 0x0010)
		seq_printf(m, "0x00000010\tMemory Uncorrectable non-fatal\n");
	if (available_error_type & 0x0020)
		seq_printf(m, "0x00000020\tMemory Uncorrectable fatal\n");
	if (available_error_type & 0x0040)
		seq_printf(m, "0x00000040\tPCI Express Correctable\n");
	if (available_error_type & 0x0080)
		seq_printf(m, "0x00000080\tPCI Express Uncorrectable non-fatal\n");
	if (available_error_type & 0x0100)
		seq_printf(m, "0x00000100\tPCI Express Uncorrectable fatal\n");
	if (available_error_type & 0x0200)
		seq_printf(m, "0x00000200\tPlatform Correctable\n");
	if (available_error_type & 0x0400)
		seq_printf(m, "0x00000400\tPlatform Uncorrectable non-fatal\n");
	if (available_error_type & 0x0800)
		seq_printf(m, "0x00000800\tPlatform Uncorrectable fatal\n");

	return 0;
}