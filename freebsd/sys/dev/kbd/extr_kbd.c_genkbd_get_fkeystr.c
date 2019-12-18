#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int kb_fkeytab_size; TYPE_1__* kb_fkeytab; } ;
typedef  TYPE_2__ keyboard_t ;
struct TYPE_4__ {size_t len; int /*<<< orphan*/ * str; } ;

/* Variables and functions */
 scalar_t__ F_FN ; 

u_char *
genkbd_get_fkeystr(keyboard_t *kbd, int fkey, size_t *len)
{
	if (kbd == NULL)
		return (NULL);
	fkey -= F_FN;
	if (fkey > kbd->kb_fkeytab_size)
		return (NULL);
	*len = kbd->kb_fkeytab[fkey].len;
	return (kbd->kb_fkeytab[fkey].str);
}