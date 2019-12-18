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
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static int
check_524(krb5_context context, const char *path, char *data)
{
    if(strcasecmp(data, "yes") == 0 ||
       strcasecmp(data, "no") == 0 ||
       strcasecmp(data, "2b") == 0 ||
       strcasecmp(data, "local") == 0)
	return 0;

    krb5_warnx(context, "%s: didn't contain a valid option `%s'",
	       path, data);
    return 1;
}