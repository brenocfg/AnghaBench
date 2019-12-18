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
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_signal ; 
 int /*<<< orphan*/  hdb_db_dir (int /*<<< orphan*/ ) ; 
 char const* krb5_config_get_string_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_mutex ; 

const char *
kadm5_log_signal_socket(krb5_context context)
{
    HEIMDAL_MUTEX_lock(&signal_mutex);
    if (!default_signal)
	asprintf(&default_signal, "%s/signal", hdb_db_dir(context));
    HEIMDAL_MUTEX_unlock(&signal_mutex);

    return krb5_config_get_string_default(context,
					  NULL,
					  default_signal,
					  "kdc",
					  "signal_socket",
					  NULL);
}