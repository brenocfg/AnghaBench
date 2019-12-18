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
typedef  char* krb5_realm ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 char** krb5_config_get_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
config_find_realm(krb5_context context,
		  const char *domain,
		  krb5_realm **realms)
{
    char **tmp = krb5_config_get_strings (context, NULL,
					  "domain_realm",
					  domain,
					  NULL);

    if (tmp == NULL)
	return -1;
    *realms = tmp;
    return 0;
}