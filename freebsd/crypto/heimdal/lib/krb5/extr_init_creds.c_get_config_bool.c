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
typedef  scalar_t__ krb5_boolean ;

/* Variables and functions */
 scalar_t__ krb5_config_get_bool_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,char*,char const*,char const*,...) ; 

__attribute__((used)) static krb5_boolean
get_config_bool (krb5_context context,
		 krb5_boolean def_value,
		 const char *realm,
		 const char *name)
{
    krb5_boolean b;

    b = krb5_config_get_bool_default(context, NULL, def_value,
				     "realms", realm, name, NULL);
    if (b != def_value)
	return b;
    b = krb5_config_get_bool_default (context, NULL, def_value,
				      "libdefaults", name, NULL);
    if (b != def_value)
	return b;
    return def_value;
}