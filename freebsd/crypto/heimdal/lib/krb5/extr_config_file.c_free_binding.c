#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_5__ {TYPE_2__* list; TYPE_2__* string; } ;
struct TYPE_6__ {scalar_t__ type; struct TYPE_6__* next; TYPE_1__ u; struct TYPE_6__* name; } ;
typedef  TYPE_2__ krb5_config_binding ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_abortx (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ krb5_config_list ; 
 scalar_t__ krb5_config_string ; 

__attribute__((used)) static void
free_binding (krb5_context context, krb5_config_binding *b)
{
    krb5_config_binding *next_b;

    while (b) {
	free (b->name);
	if (b->type == krb5_config_string)
	    free (b->u.string);
	else if (b->type == krb5_config_list)
	    free_binding (context, b->u.list);
	else
	    krb5_abortx(context, "unknown binding type (%d) in free_binding",
			b->type);
	next_b = b->next;
	free (b);
	b = next_b;
    }
}