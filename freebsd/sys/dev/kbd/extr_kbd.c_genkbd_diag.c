#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int kb_index; char* kb_name; char* kb_unit; int kb_type; int kb_config; scalar_t__ kb_io_base; scalar_t__ kb_io_size; int /*<<< orphan*/  kb_flags; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int get_kbd_type_name (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
genkbd_diag(keyboard_t *kbd, int level)
{
	if (level > 0) {
		printf("kbd%d: %s%d, %s (%d), config:0x%x, flags:0x%x",
		    kbd->kb_index, kbd->kb_name, kbd->kb_unit,
		    get_kbd_type_name(kbd->kb_type), kbd->kb_type,
		    kbd->kb_config, kbd->kb_flags);
		if (kbd->kb_io_base > 0)
			printf(", port:0x%x-0x%x", kbd->kb_io_base,
			    kbd->kb_io_base + kbd->kb_io_size - 1);
		printf("\n");
	}
}