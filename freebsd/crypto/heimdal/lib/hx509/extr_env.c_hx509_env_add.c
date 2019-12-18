#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* hx509_env ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_6__ {int /*<<< orphan*/ * string; } ;
struct TYPE_7__ {struct TYPE_7__* next; struct TYPE_7__* name; TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  env_string ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 TYPE_2__* malloc (int) ; 
 void* strdup (char const*) ; 

int
hx509_env_add(hx509_context context, hx509_env *env,
	      const char *key, const char *value)
{
    hx509_env n;

    n = malloc(sizeof(*n));
    if (n == NULL) {
	hx509_set_error_string(context, 0, ENOMEM, "out of memory");
	return ENOMEM;
    }

    n->type = env_string;
    n->next = NULL;
    n->name = strdup(key);
    if (n->name == NULL) {
	free(n);
	return ENOMEM;
    }
    n->u.string = strdup(value);
    if (n->u.string == NULL) {
	free(n->name);
	free(n);
	return ENOMEM;
    }

    /* add to tail */
    if (*env) {
	hx509_env e = *env;
	while (e->next)
	    e = e->next;
	e->next = n;
    } else
	*env = n;

    return 0;
}