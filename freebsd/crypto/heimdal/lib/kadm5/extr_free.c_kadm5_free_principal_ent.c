#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* tl_data_contents; int /*<<< orphan*/  tl_data_length; struct TYPE_8__* tl_data_next; } ;
typedef  TYPE_1__ krb5_tl_data ;
struct TYPE_9__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ kadm5_server_context ;
typedef  TYPE_3__* kadm5_principal_ent_t ;
struct TYPE_10__ {TYPE_1__* key_data; scalar_t__ n_tl_data; TYPE_1__* tl_data; int /*<<< orphan*/  n_key_data; int /*<<< orphan*/  mod_name; int /*<<< orphan*/  principal; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  kadm5_free_key_data (void*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kadm5_free_principal_ent(void *server_handle,
			 kadm5_principal_ent_t princ)
{
    kadm5_server_context *context = server_handle;
    if(princ->principal)
	krb5_free_principal(context->context, princ->principal);
    if(princ->mod_name)
	krb5_free_principal(context->context, princ->mod_name);
    kadm5_free_key_data(server_handle, &princ->n_key_data, princ->key_data);
    while(princ->n_tl_data && princ->tl_data) {
	krb5_tl_data *tp;
	tp = princ->tl_data;
	princ->tl_data = tp->tl_data_next;
	princ->n_tl_data--;
	memset(tp->tl_data_contents, 0, tp->tl_data_length);
	free(tp->tl_data_contents);
	free(tp);
    }
    if (princ->key_data != NULL)
	free (princ->key_data);
}