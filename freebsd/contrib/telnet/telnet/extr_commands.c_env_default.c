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
struct env_lst {int welldefined; unsigned char* var; scalar_t__ export; struct env_lst* next; } ;

/* Variables and functions */
 struct env_lst envlisthead ; 

unsigned char *
env_default(int init, int welldefined)
{
	static struct env_lst *nep = NULL;

	if (init) {
		nep = &envlisthead;
		return(NULL);
	}
	if (nep) {
		while ((nep = nep->next)) {
			if (nep->export && (nep->welldefined == welldefined))
				return(nep->var);
		}
	}
	return(NULL);
}