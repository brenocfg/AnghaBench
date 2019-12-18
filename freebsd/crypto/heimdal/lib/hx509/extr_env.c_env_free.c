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
typedef  TYPE_2__* hx509_env ;
struct TYPE_5__ {TYPE_2__* list; TYPE_2__* string; } ;
struct TYPE_6__ {scalar_t__ type; struct TYPE_6__* name; TYPE_1__ u; struct TYPE_6__* next; } ;

/* Variables and functions */
 scalar_t__ env_list ; 
 scalar_t__ env_string ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void
env_free(hx509_env b)
{
    while(b) {
	hx509_env next = b->next;

	if (b->type == env_string)
	    free(b->u.string);
	else if (b->type == env_list)
	    env_free(b->u.list);

	free(b->name);
	free(b);
	b = next;
    }
}