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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRNTSTYL_COMP ; 
 int /*<<< orphan*/  TIDTYPE_TCB ; 
 int /*<<< orphan*/  chip_id ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int /*<<< orphan*/  parse_n_display_xcb (unsigned char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_print_style (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tcb_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swizzle_tcb (unsigned char*) ; 

__attribute__((used)) static void
show_tcb(uint32_t *buf, uint32_t len)
{
	unsigned char *tcb = (unsigned char *)buf;
	const char *s;
	int i, n = 8;

	while (len) {
		for (i = 0; len && i < n; i++, buf++, len -= 4) {
			s = i ? " " : "";
			printf("%s%08x", s, htonl(*buf));
		}
		printf("\n");
	}
	set_tcb_info(TIDTYPE_TCB, chip_id);
	set_print_style(PRNTSTYL_COMP);
	swizzle_tcb(tcb);
	parse_n_display_xcb(tcb);
}