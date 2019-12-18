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
struct client {scalar_t__ logging; scalar_t__ sock; struct client* moniker; TYPE_1__* handles; } ;
struct TYPE_2__ {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_handle (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct client*) ; 
 int /*<<< orphan*/  krb5_storage_free (scalar_t__) ; 

__attribute__((used)) static void
free_client(struct client *c)
{
    while(c->handles)
	del_handle(&c->handles, c->handles->idx);

    free(c->moniker);
    krb5_storage_free(c->sock);
    if (c->logging)
	krb5_storage_free(c->logging);
    free(c);
}