#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  gss_OID ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_NO_OID ; 
 int /*<<< orphan*/  GSS_KRB5_MECHANISM ; 
 int /*<<< orphan*/  GSS_SPNEGO_MECHANISM ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

gss_OID
select_mech(const char *mech)
{
    if (strcasecmp(mech, "krb5") == 0)
	return GSS_KRB5_MECHANISM;
    else if (strcasecmp(mech, "spnego") == 0)
	return GSS_SPNEGO_MECHANISM;
    else if (strcasecmp(mech, "no-oid") == 0)
	return GSS_C_NO_OID;
    else
	errx (1, "Unknown mechanism '%s' (spnego, krb5, no-oid)", mech);
}