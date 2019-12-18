#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int type; int /*<<< orphan*/ * name; struct TYPE_6__* next; } ;
typedef  TYPE_1__ krb5_config_section ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int krb5_config_list ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

krb5_config_section *
_krb5_config_get_entry(krb5_config_section **parent, const char *name, int type)
{
    krb5_config_section **q;

    for(q = parent; *q != NULL; q = &(*q)->next)
	if(type == krb5_config_list &&
	   (unsigned)type == (*q)->type &&
	   strcmp(name, (*q)->name) == 0)
	    return *q;
    *q = calloc(1, sizeof(**q));
    if(*q == NULL)
	return NULL;
    (*q)->name = strdup(name);
    (*q)->type = type;
    if((*q)->name == NULL) {
	free(*q);
	*q = NULL;
	return NULL;
    }
    return *q;
}