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
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_1__* kadm5_principal_ent_t ;
struct TYPE_3__ {int /*<<< orphan*/  attributes; int /*<<< orphan*/  pw_expiration; int /*<<< orphan*/  princ_expire_time; int /*<<< orphan*/  max_renewable_life; int /*<<< orphan*/  max_life; } ;

/* Variables and functions */
 int /*<<< orphan*/  KADM5_ATTRIBUTES ; 
 int /*<<< orphan*/  KADM5_MAX_LIFE ; 
 int /*<<< orphan*/  KADM5_MAX_RLIFE ; 
 int /*<<< orphan*/  KADM5_PRINC_EXPIRE_TIME ; 
 int /*<<< orphan*/  KADM5_PW_EXPIRATION ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ parse_attributes (char const*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_deltat (char const*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_timet (char const*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

int
set_entry(krb5_context contextp,
	  kadm5_principal_ent_t ent,
	  int *mask,
	  const char *max_ticket_life,
	  const char *max_renewable_life,
	  const char *expiration,
	  const char *pw_expiration,
	  const char *attributes)
{
    if (max_ticket_life != NULL) {
	if (parse_deltat (max_ticket_life, &ent->max_life,
			  mask, KADM5_MAX_LIFE)) {
	    krb5_warnx (contextp, "unable to parse `%s'", max_ticket_life);
	    return 1;
	}
    }
    if (max_renewable_life != NULL) {
	if (parse_deltat (max_renewable_life, &ent->max_renewable_life,
			  mask, KADM5_MAX_RLIFE)) {
	    krb5_warnx (contextp, "unable to parse `%s'", max_renewable_life);
	    return 1;
	}
    }

    if (expiration) {
	if (parse_timet (expiration, &ent->princ_expire_time,
			mask, KADM5_PRINC_EXPIRE_TIME)) {
	    krb5_warnx (contextp, "unable to parse `%s'", expiration);
	    return 1;
	}
    }
    if (pw_expiration) {
	if (parse_timet (pw_expiration, &ent->pw_expiration,
			 mask, KADM5_PW_EXPIRATION)) {
	    krb5_warnx (contextp, "unable to parse `%s'", pw_expiration);
	    return 1;
	}
    }
    if (attributes != NULL) {
	if (parse_attributes (attributes, &ent->attributes,
			      mask, KADM5_ATTRIBUTES)) {
	    krb5_warnx (contextp, "unable to parse `%s'", attributes);
	    return 1;
	}
    }
    return 0;
}