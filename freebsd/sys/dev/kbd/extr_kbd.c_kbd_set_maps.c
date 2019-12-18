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
typedef  int /*<<< orphan*/  keymap_t ;
struct TYPE_3__ {int kb_fkeytab_size; int /*<<< orphan*/ * kb_fkeytab; int /*<<< orphan*/ * kb_accentmap; int /*<<< orphan*/ * kb_keymap; } ;
typedef  TYPE_1__ keyboard_t ;
typedef  int /*<<< orphan*/  fkeytab_t ;
typedef  int /*<<< orphan*/  accentmap_t ;

/* Variables and functions */

void
kbd_set_maps(keyboard_t *kbd, keymap_t *keymap, accentmap_t *accmap,
	     fkeytab_t *fkeymap, int fkeymap_size)
{
	kbd->kb_keymap = keymap;
	kbd->kb_accentmap = accmap;
	kbd->kb_fkeytab = fkeymap;
	kbd->kb_fkeytab_size = fkeymap_size;
}