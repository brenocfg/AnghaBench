#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  caller; int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ kadm5_server_context ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;
struct TYPE_8__ {TYPE_3__* modified_by; } ;
typedef  TYPE_2__ hdb_entry ;
struct TYPE_9__ {int /*<<< orphan*/  principal; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  free_Event (TYPE_3__*) ; 
 int /*<<< orphan*/  krb5_copy_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

kadm5_ret_t
_kadm5_set_modifier(kadm5_server_context *context,
		    hdb_entry *ent)
{
    kadm5_ret_t ret;
    if(ent->modified_by == NULL){
	ent->modified_by = malloc(sizeof(*ent->modified_by));
	if(ent->modified_by == NULL)
	    return ENOMEM;
    } else
	free_Event(ent->modified_by);
    ent->modified_by->time = time(NULL);
    ret = krb5_copy_principal(context->context, context->caller,
			      &ent->modified_by->principal);
    return ret;
}