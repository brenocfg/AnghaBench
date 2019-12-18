#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_4__ {TYPE_1__* mb; } ;
struct TYPE_3__ {int /*<<< orphan*/  tplname; } ;

/* Variables and functions */
 int ENOENT ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  TPL_LIST_RLOCK () ; 
 int /*<<< orphan*/  TPL_LIST_RUNLOCK () ; 
 size_t ntpl ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 TYPE_2__** tpllist ; 

int
stats_tpl_id2name(uint32_t tpl_id, char *buf, size_t len)
{
	int error;

	error = 0;

	TPL_LIST_RLOCK();
	if (tpl_id < ntpl) {
		if (buf != NULL && len > strlen(tpllist[tpl_id]->mb->tplname))
			strlcpy(buf, tpllist[tpl_id]->mb->tplname, len);
		else
			error = EOVERFLOW;
	} else
		error = ENOENT;
	TPL_LIST_RUNLOCK();

	return (error);
}