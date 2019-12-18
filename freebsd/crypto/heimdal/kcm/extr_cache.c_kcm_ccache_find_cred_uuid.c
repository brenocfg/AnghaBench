#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kcm_creds {int /*<<< orphan*/  uuid; struct kcm_creds* next; } ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kcmuuid_t ;
typedef  TYPE_1__* kcm_ccache ;
struct TYPE_3__ {struct kcm_creds* creds; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct kcm_creds *
kcm_ccache_find_cred_uuid(krb5_context context,
			  kcm_ccache ccache,
			  kcmuuid_t uuid)
{
    struct kcm_creds *c;

    for (c = ccache->creds; c != NULL; c = c->next)
	if (memcmp(c->uuid, uuid, sizeof(c->uuid)) == 0)
	    return c;

    return NULL;
}