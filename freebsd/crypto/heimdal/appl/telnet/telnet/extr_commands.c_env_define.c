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
struct env_lst {unsigned char* var; unsigned char* value; int export; int /*<<< orphan*/  welldefined; struct env_lst* prev; struct env_lst* next; } ;

/* Variables and functions */
 struct env_lst* env_find (unsigned char*) ; 
 struct env_lst envlisthead ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  opt_welldefined (char*) ; 
 scalar_t__ strdup (char*) ; 

struct env_lst *
env_define(unsigned char *var, unsigned char *value)
{
	struct env_lst *ep;

	if ((ep = env_find(var))) {
		if (ep->var)
			free(ep->var);
		if (ep->value)
			free(ep->value);
	} else {
		ep = (struct env_lst *)malloc(sizeof(struct env_lst));
		ep->next = envlisthead.next;
		envlisthead.next = ep;
		ep->prev = &envlisthead;
		if (ep->next)
			ep->next->prev = ep;
	}
	ep->welldefined = opt_welldefined((char *)var);
	ep->export = 1;
	ep->var = (unsigned char *)strdup((char *)var);
	ep->value = (unsigned char *)strdup((char *)value);
	return(ep);
}