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
typedef  char u_int ;
struct acc_t {char accchar; char** map; } ;
struct TYPE_5__ {TYPE_1__* kb_accentmap; } ;
typedef  TYPE_2__ keyboard_t ;
struct TYPE_4__ {struct acc_t* acc; } ;

/* Variables and functions */
 char ERRKEY ; 
 int NUM_ACCENTCHARS ; 

__attribute__((used)) static u_int
make_accent_char(keyboard_t *kbd, u_int ch, int *accents)
{
	struct acc_t *acc;
	int i;

	acc = &kbd->kb_accentmap->acc[*accents - 1];
	*accents = 0;

	/*
	 * If the accent key is followed by the space key,
	 * produce the accent char itself.
	 */
	if (ch == ' ')
		return (acc->accchar);

	/* scan the accent map */
	for (i = 0; i < NUM_ACCENTCHARS; ++i) {
		if (acc->map[i][0] == 0)	/* end of table */
			break;
		if (acc->map[i][0] == ch)
			return (acc->map[i][1]);
	}
	/* this char cannot be accented... */
	return (ERRKEY);
}