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
struct ng_type {int refs; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  LIST_REMOVE (struct ng_type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRAP_ERROR () ; 
 int /*<<< orphan*/  TYPELIST_WLOCK () ; 
 int /*<<< orphan*/  TYPELIST_WUNLOCK () ; 
 int /*<<< orphan*/  types ; 

int
ng_rmtype(struct ng_type *tp)
{
	/* Check for name collision */
	if (tp->refs != 1) {
		TRAP_ERROR();
		return (EBUSY);
	}

	/* Unlink type */
	TYPELIST_WLOCK();
	LIST_REMOVE(tp, types);
	TYPELIST_WUNLOCK();
	return (0);
}