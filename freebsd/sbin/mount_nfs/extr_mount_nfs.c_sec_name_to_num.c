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
 int AUTH_SYS ; 
 int RPCSEC_GSS_KRB5 ; 
 int RPCSEC_GSS_KRB5I ; 
 int RPCSEC_GSS_KRB5P ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int
sec_name_to_num(const char *sec)
{
	if (!strcmp(sec, "krb5"))
		return (RPCSEC_GSS_KRB5);
	if (!strcmp(sec, "krb5i"))
		return (RPCSEC_GSS_KRB5I);
	if (!strcmp(sec, "krb5p"))
		return (RPCSEC_GSS_KRB5P);
	if (!strcmp(sec, "sys"))
		return (AUTH_SYS);
	return (-1);
}