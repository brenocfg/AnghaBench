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
struct statsblob_tpl {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  TPL_LIST_WLOCK () ; 
 int /*<<< orphan*/  TPL_LIST_WUNLOCK () ; 
 scalar_t__ ntpl ; 
 struct statsblob_tpl** tpllist ; 

int
stats_tpl_fetch(int tpl_id, struct statsblob_tpl **tpl)
{
	int error;

	error = 0;

	TPL_LIST_WLOCK();
	if (tpl_id < 0 || tpl_id >= (int)ntpl) {
		error = ENOENT;
	} else {
		*tpl = tpllist[tpl_id];
		/* XXXLAS: Acquire refcount on tpl. */
	}
	TPL_LIST_WUNLOCK();

	return (error);
}