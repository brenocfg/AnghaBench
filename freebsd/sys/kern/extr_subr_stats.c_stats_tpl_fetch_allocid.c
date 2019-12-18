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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {TYPE_1__* mb; } ;
struct TYPE_3__ {char const* tplname; scalar_t__ tplhash; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  TPL_LIST_RLOCK () ; 
 int /*<<< orphan*/  TPL_LIST_RUNLOCK () ; 
 int /*<<< orphan*/  TPL_MAX_NAME_LEN ; 
 int ntpl ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_2__** tpllist ; 

int
stats_tpl_fetch_allocid(const char *name, uint32_t hash)
{
	int i, tpl_id;

	tpl_id = -ESRCH;

	TPL_LIST_RLOCK();
	for (i = ntpl - 1; i >= 0; i--) {
		if (name != NULL) {
			if (strlen(name) == strlen(tpllist[i]->mb->tplname) &&
			    strncmp(name, tpllist[i]->mb->tplname,
			    TPL_MAX_NAME_LEN) == 0 && (!hash || hash ==
			    tpllist[i]->mb->tplhash)) {
				tpl_id = i;
				break;
			}
		} else if (hash == tpllist[i]->mb->tplhash) {
			tpl_id = i;
			break;
		}
	}
	TPL_LIST_RUNLOCK();

	return (tpl_id);
}