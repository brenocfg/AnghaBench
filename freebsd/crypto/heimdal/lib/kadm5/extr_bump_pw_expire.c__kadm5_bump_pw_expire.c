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
typedef  scalar_t__ time_t ;
struct TYPE_5__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ kadm5_server_context ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;
struct TYPE_6__ {scalar_t__* pw_end; } ;
typedef  TYPE_2__ hdb_entry ;

/* Variables and functions */
 scalar_t__ krb5_config_get_time_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

kadm5_ret_t
_kadm5_bump_pw_expire(kadm5_server_context *context,
		      hdb_entry *ent)
{
    if (ent->pw_end != NULL) {
	time_t life;

	life = krb5_config_get_time_default(context->context,
					    NULL,
					    365 * 24 * 60 * 60,
					    "kadmin",
					    "password_lifetime",
					    NULL);

	*(ent->pw_end) = time(NULL) + life;
    }
    return 0;
}