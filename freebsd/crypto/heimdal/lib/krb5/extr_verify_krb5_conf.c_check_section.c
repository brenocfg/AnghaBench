#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct entry {char* name; scalar_t__ type; scalar_t__ deprecated; struct entry* check_data; } ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_4__ {TYPE_2__* list; int /*<<< orphan*/  string; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ u; int /*<<< orphan*/  name; struct TYPE_5__* next; } ;
typedef  TYPE_2__ krb5_config_section ;
typedef  int (* check_func_t ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ krb5_config_list ; 
 scalar_t__ krb5_config_string ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_section(krb5_context context, const char *path, krb5_config_section *cf,
	      struct entry *entries)
{
    int error = 0;
    krb5_config_section *p;
    struct entry *e;

    char *local;

    for(p = cf; p != NULL; p = p->next) {
	local = NULL;
	if (asprintf(&local, "%s/%s", path, p->name) < 0 || local == NULL)
	    errx(1, "out of memory");
	for(e = entries; e->name != NULL; e++) {
	    if(*e->name == '\0' || strcmp(e->name, p->name) == 0) {
		if(e->type != p->type) {
		    krb5_warnx(context, "%s: unknown or wrong type", local);
		    error |= 1;
		} else if(p->type == krb5_config_string && e->check_data != NULL) {
		    error |= (*(check_func_t)e->check_data)(context, local, p->u.string);
		} else if(p->type == krb5_config_list && e->check_data != NULL) {
		    error |= check_section(context, local, p->u.list, e->check_data);
		}
		if(e->deprecated) {
		    krb5_warnx(context, "%s: is a deprecated entry", local);
		    error |= 1;
		}
		break;
	    }
	}
	if(e->name == NULL) {
	    krb5_warnx(context, "%s: unknown entry", local);
	    error |= 1;
	}
	free(local);
    }
    return error;
}