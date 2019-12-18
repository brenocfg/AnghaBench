#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* kadm5_principal_ent_t ;
struct TYPE_4__ {int attributes; int /*<<< orphan*/  pw_expiration; int /*<<< orphan*/  princ_expire_time; int /*<<< orphan*/  max_renewable_life; int /*<<< orphan*/  max_life; } ;

/* Variables and functions */
 int KADM5_ATTRIBUTES ; 
 int KADM5_MAX_LIFE ; 
 int KADM5_MAX_RLIFE ; 
 int KADM5_PRINC_EXPIRE_TIME ; 
 int KADM5_PW_EXPIRATION ; 
 int KRB5_KDB_DISALLOW_ALL_TIX ; 

void
set_defaults(kadm5_principal_ent_t ent, int *mask,
	     kadm5_principal_ent_t default_ent, int default_mask)
{
    if (default_ent
	&& (default_mask & KADM5_MAX_LIFE)
	&& !(*mask & KADM5_MAX_LIFE))
	ent->max_life = default_ent->max_life;

    if (default_ent
	&& (default_mask & KADM5_MAX_RLIFE)
	&& !(*mask & KADM5_MAX_RLIFE))
	ent->max_renewable_life = default_ent->max_renewable_life;

    if (default_ent
	&& (default_mask & KADM5_PRINC_EXPIRE_TIME)
	&& !(*mask & KADM5_PRINC_EXPIRE_TIME))
	ent->princ_expire_time = default_ent->princ_expire_time;

    if (default_ent
	&& (default_mask & KADM5_PW_EXPIRATION)
	&& !(*mask & KADM5_PW_EXPIRATION))
	ent->pw_expiration = default_ent->pw_expiration;

    if (default_ent
	&& (default_mask & KADM5_ATTRIBUTES)
	&& !(*mask & KADM5_ATTRIBUTES))
	ent->attributes = default_ent->attributes & ~KRB5_KDB_DISALLOW_ALL_TIX;
}