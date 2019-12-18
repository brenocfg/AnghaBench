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
struct _heimdal_syslog_data {int priority; } ;
struct TYPE_4__ {int /*<<< orphan*/  program; } ;
typedef  TYPE_1__ krb5_log_facility ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int LOG_AUTH ; 
 int LOG_ERR ; 
 int LOG_NDELAY ; 
 int LOG_PID ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  close_syslog ; 
 int find_value (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_addlog_func (int /*<<< orphan*/ ,TYPE_1__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct _heimdal_syslog_data*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_syslog ; 
 struct _heimdal_syslog_data* malloc (int) ; 
 int /*<<< orphan*/  roken_openlog (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  syslogvals ; 

__attribute__((used)) static krb5_error_code
open_syslog(krb5_context context,
	    krb5_log_facility *facility, int min, int max,
	    const char *sev, const char *fac)
{
    struct _heimdal_syslog_data *sd = malloc(sizeof(*sd));
    int i;

    if(sd == NULL) {
	krb5_set_error_message(context, ENOMEM,
			       N_("malloc: out of memory", ""));
	return ENOMEM;
    }
    i = find_value(sev, syslogvals);
    if(i == -1)
	i = LOG_ERR;
    sd->priority = i;
    i = find_value(fac, syslogvals);
    if(i == -1)
	i = LOG_AUTH;
    sd->priority |= i;
    roken_openlog(facility->program, LOG_PID | LOG_NDELAY, i);
    return krb5_addlog_func(context, facility, min, max,
			    log_syslog, close_syslog, sd);
}