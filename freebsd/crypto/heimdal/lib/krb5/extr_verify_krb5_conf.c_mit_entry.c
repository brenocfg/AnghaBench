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
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ warn_mit_syntax_flag ; 

__attribute__((used)) static int
mit_entry(krb5_context context, const char *path, char *data)
{
    if (warn_mit_syntax_flag)
	krb5_warnx(context, "%s is only used by MIT Kerberos", path);
    return 0;
}