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
struct eqn_node {char* data; int sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int mandoc_asprintf (char**,char*,char*,char const*) ; 
 char* mandoc_strdup (char const*) ; 
 int strlen (char const*) ; 

void
eqn_read(struct eqn_node *ep, const char *p)
{
	char		*cp;

	if (ep->data == NULL) {
		ep->sz = strlen(p);
		ep->data = mandoc_strdup(p);
	} else {
		ep->sz = mandoc_asprintf(&cp, "%s %s", ep->data, p);
		free(ep->data);
		ep->data = cp;
	}
	ep->sz += 1;
}