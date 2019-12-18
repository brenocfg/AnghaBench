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
typedef  int uintmax_t ;
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {char const* size; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 int device_get_nameunit (int /*<<< orphan*/ ) ; 
 unsigned int pram_nreg ; 
 TYPE_1__* pram_segments ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int,...) ; 
 int /*<<< orphan*/  sbuf_printf_drain ; 
 int /*<<< orphan*/  sbuf_putc (struct sbuf*,char) ; 
 int /*<<< orphan*/  sbuf_set_drain (struct sbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvdimm_e820_dump_prams(device_t dev, const char *func, int hintunit)
{
	char buffer[256];
	struct sbuf sb;
	bool printed = false;
	unsigned i;

	sbuf_new(&sb, buffer, sizeof(buffer), SBUF_FIXEDLEN);
	sbuf_set_drain(&sb, sbuf_printf_drain, NULL);

	sbuf_printf(&sb, "%s: %s: ", device_get_nameunit(dev), func);
	if (hintunit < 0)
		sbuf_cat(&sb, "Found BIOS PRAM regions: ");
	else
		sbuf_printf(&sb, "Remaining unallocated PRAM regions after "
		    "hint %d: ", hintunit);

	for (i = 0; i < pram_nreg; i++) {
		if (pram_segments[i].size == 0)
			continue;
		if (printed)
			sbuf_putc(&sb, ',');
		else
			printed = true;
		sbuf_printf(&sb, "0x%jx-0x%jx",
		    (uintmax_t)pram_segments[i].start,
		    (uintmax_t)pram_segments[i].start + pram_segments[i].size
		    - 1);
	}

	if (!printed)
		sbuf_cat(&sb, "<none>");
	sbuf_putc(&sb, '\n');
	sbuf_finish(&sb);
	sbuf_delete(&sb);
}