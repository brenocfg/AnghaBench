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

/* Variables and functions */
 char* aix_krb5_get_principal_name (char const*) ; 

char *
platform_krb5_get_principal_name(const char *pw_name)
{
#ifdef USE_AIX_KRB_NAME
	return aix_krb5_get_principal_name(pw_name);
#else
	return NULL;
#endif
}