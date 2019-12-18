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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 scalar_t__ copy_hostname (int /*<<< orphan*/ ,char const*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ krb5_get_host_realm (int /*<<< orphan*/ ,char*,char***) ; 
 int /*<<< orphan*/  strlwr (char*) ; 

__attribute__((used)) static krb5_error_code
vanilla_hostname (krb5_context context,
		  const char *orig_hostname,
		  char **new_hostname,
		  char ***realms)
{
    krb5_error_code ret;

    ret = copy_hostname (context, orig_hostname, new_hostname);
    if (ret)
	return ret;
    strlwr (*new_hostname);

    ret = krb5_get_host_realm (context, *new_hostname, realms);
    if (ret) {
	free (*new_hostname);
	return ret;
    }
    return 0;
}