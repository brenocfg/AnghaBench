#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kadm5_ret_t ;
struct TYPE_2__ {int /*<<< orphan*/  context; scalar_t__ my_context; int /*<<< orphan*/ * ac; scalar_t__ service_name; scalar_t__ client_name; int /*<<< orphan*/  sock; scalar_t__ admin_server; scalar_t__ realm; } ;
typedef  TYPE_1__ kadm5_client_context ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  krb5_auth_con_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 

kadm5_ret_t
kadm5_c_destroy(void *server_handle)
{
    kadm5_client_context *context = server_handle;

    free(context->realm);
    free(context->admin_server);
    close(context->sock);
    if (context->client_name)
	free(context->client_name);
    if (context->service_name)
	free(context->service_name);
    if (context->ac != NULL)
	krb5_auth_con_free(context->context, context->ac);
    if(context->my_context)
	krb5_free_context(context->context);
    return 0;
}