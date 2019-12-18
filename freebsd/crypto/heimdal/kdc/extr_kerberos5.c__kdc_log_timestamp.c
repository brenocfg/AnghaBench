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
typedef  int /*<<< orphan*/  starttime_str ;
typedef  int /*<<< orphan*/  renewtime_str ;
typedef  int /*<<< orphan*/  krb5_kdc_configuration ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  endtime_str ;
typedef  int /*<<< orphan*/  authtime_str ;
typedef  int /*<<< orphan*/  KerberosTime ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kdc_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,char const*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  krb5_format_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

void
_kdc_log_timestamp(krb5_context context,
		   krb5_kdc_configuration *config,
		   const char *type,
		   KerberosTime authtime, KerberosTime *starttime,
		   KerberosTime endtime, KerberosTime *renew_till)
{
    char authtime_str[100], starttime_str[100],
	endtime_str[100], renewtime_str[100];

    krb5_format_time(context, authtime,
		     authtime_str, sizeof(authtime_str), TRUE);
    if (starttime)
	krb5_format_time(context, *starttime,
			 starttime_str, sizeof(starttime_str), TRUE);
    else
	strlcpy(starttime_str, "unset", sizeof(starttime_str));
    krb5_format_time(context, endtime,
		     endtime_str, sizeof(endtime_str), TRUE);
    if (renew_till)
	krb5_format_time(context, *renew_till,
			 renewtime_str, sizeof(renewtime_str), TRUE);
    else
	strlcpy(renewtime_str, "unset", sizeof(renewtime_str));

    kdc_log(context, config, 5,
	    "%s authtime: %s starttime: %s endtime: %s renew till: %s",
	    type, authtime_str, starttime_str, endtime_str, renewtime_str);
}