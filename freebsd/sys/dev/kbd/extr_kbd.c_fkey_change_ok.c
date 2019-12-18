#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ fkeytab_t ;
struct TYPE_6__ {scalar_t__ flen; int /*<<< orphan*/  keydef; } ;
typedef  TYPE_2__ fkeyarg_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRIV_KEYBOARD ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int keymap_restrict_change ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fkey_change_ok(fkeytab_t *oldkey, fkeyarg_t *newkey, struct thread *td)
{
	if (keymap_restrict_change <= 3)
		return (0);

	if (oldkey->len != newkey->flen ||
	    bcmp(oldkey->str, newkey->keydef, oldkey->len) != 0)
		return priv_check(td, PRIV_KEYBOARD);

	return (0);
}