#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_7__ {TYPE_1__* kb_accentmap; } ;
typedef  TYPE_3__ keyboard_t ;
struct TYPE_6__ {scalar_t__ accchar; } ;
struct TYPE_5__ {int n_accs; TYPE_2__* acc; } ;

/* Variables and functions */
 int ERRKEY ; 
 int F_ACC ; 
 int NOKEY ; 

__attribute__((used)) static u_int
save_accent_key(keyboard_t *kbd, u_int key, int *accents)
{
	int i;

	/* make an index into the accent map */
	i = key - F_ACC + 1;
	if ((i > kbd->kb_accentmap->n_accs)
	    || (kbd->kb_accentmap->acc[i - 1].accchar == 0)) {
		/* the index is out of range or pointing to an empty entry */
		*accents = 0;
		return (ERRKEY);
	}

	/*
	 * If the same accent key has been hit twice, produce the accent
	 * char itself.
	 */
	if (i == *accents) {
		key = kbd->kb_accentmap->acc[i - 1].accchar;
		*accents = 0;
		return (key);
	}

	/* remember the index and wait for the next key  */
	*accents = i;
	return (NOKEY);
}