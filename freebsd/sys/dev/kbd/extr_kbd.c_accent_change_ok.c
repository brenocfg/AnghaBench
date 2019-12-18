#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct acc_t {scalar_t__ accchar; scalar_t__** map; } ;
struct TYPE_4__ {int n_accs; struct acc_t* acc; } ;
typedef  TYPE_1__ accentmap_t ;

/* Variables and functions */
 int NUM_ACCENTCHARS ; 
 int /*<<< orphan*/  PRIV_KEYBOARD ; 
 int keymap_restrict_change ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
accent_change_ok(accentmap_t *oldmap, accentmap_t *newmap, struct thread *td)
{
	struct acc_t *oldacc, *newacc;
	int accent, i;

	if (keymap_restrict_change <= 2)
		return (0);

	if (oldmap->n_accs != newmap->n_accs)
		return priv_check(td, PRIV_KEYBOARD);

	for (accent = 0; accent < oldmap->n_accs; accent++) {
		oldacc = &oldmap->acc[accent];
		newacc = &newmap->acc[accent];
		if (oldacc->accchar != newacc->accchar)
			return priv_check(td, PRIV_KEYBOARD);
		for (i = 0; i < NUM_ACCENTCHARS; ++i) {
			if (oldacc->map[i][0] != newacc->map[i][0])
				return priv_check(td, PRIV_KEYBOARD);
			if (oldacc->map[i][0] == 0)	/* end of table */
				break;
			if (oldacc->map[i][1] != newacc->map[i][1])
				return priv_check(td, PRIV_KEYBOARD);
		}
	}

	return (0);
}