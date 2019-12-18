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
struct sock_list {struct sock_list* next; } ;
struct regional {int dummy; } ;

/* Variables and functions */
 scalar_t__ VERB_ALGO ; 
 int /*<<< orphan*/  sock_list_insert (struct sock_list**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct regional*) ; 
 int /*<<< orphan*/  sock_list_logentry (scalar_t__,char*,struct sock_list*) ; 
 int /*<<< orphan*/  sock_list_merge (struct sock_list**,struct regional*,struct sock_list*) ; 
 int /*<<< orphan*/  sock_list_prepend (struct sock_list**,struct sock_list*) ; 
 int /*<<< orphan*/  verbose (scalar_t__,char*) ; 
 scalar_t__ verbosity ; 

void val_blacklist(struct sock_list** blacklist, struct regional* region,
	struct sock_list* origin, int cross)
{
	/* debug printout */
	if(verbosity >= VERB_ALGO) {
		struct sock_list* p;
		for(p=*blacklist; p; p=p->next)
			sock_list_logentry(VERB_ALGO, "blacklist", p);
		if(!origin)
			verbose(VERB_ALGO, "blacklist add: cache");
		for(p=origin; p; p=p->next)
			sock_list_logentry(VERB_ALGO, "blacklist add", p);
	}
	/* blacklist the IPs or the cache */
	if(!origin) {
		/* only add if nothing there. anything else also stops cache*/
		if(!*blacklist)
			sock_list_insert(blacklist, NULL, 0, region);
	} else if(!cross)
		sock_list_prepend(blacklist, origin);
	else	sock_list_merge(blacklist, region, origin);
}