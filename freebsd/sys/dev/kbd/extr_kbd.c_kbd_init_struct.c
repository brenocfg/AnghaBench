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
struct TYPE_3__ {char* kb_name; int kb_type; int kb_unit; int kb_config; int kb_io_base; int kb_io_size; long kb_count; int /*<<< orphan*/  kb_lastact; int /*<<< orphan*/  kb_delay2; int /*<<< orphan*/  kb_delay1; scalar_t__ kb_fkeytab_size; int /*<<< orphan*/ * kb_fkeytab; int /*<<< orphan*/ * kb_accentmap; int /*<<< orphan*/ * kb_keymap; int /*<<< orphan*/ * kb_data; scalar_t__ kb_led; int /*<<< orphan*/  kb_flags; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int KB_CONF_PROBE_ONLY ; 
 int /*<<< orphan*/  KB_DELAY1 ; 
 int /*<<< orphan*/  KB_DELAY2 ; 
 int /*<<< orphan*/  KB_NO_DEVICE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 

void
kbd_init_struct(keyboard_t *kbd, char *name, int type, int unit, int config,
		int port, int port_size)
{
	kbd->kb_flags = KB_NO_DEVICE;	/* device has not been found */
	kbd->kb_name = name;
	kbd->kb_type = type;
	kbd->kb_unit = unit;
	kbd->kb_config = config & ~KB_CONF_PROBE_ONLY;
	kbd->kb_led = 0;		/* unknown */
	kbd->kb_io_base = port;
	kbd->kb_io_size = port_size;
	kbd->kb_data = NULL;
	kbd->kb_keymap = NULL;
	kbd->kb_accentmap = NULL;
	kbd->kb_fkeytab = NULL;
	kbd->kb_fkeytab_size = 0;
	kbd->kb_delay1 = KB_DELAY1;	/* these values are advisory only */
	kbd->kb_delay2 = KB_DELAY2;
	kbd->kb_count = 0L;
	bzero(kbd->kb_lastact, sizeof(kbd->kb_lastact));
}