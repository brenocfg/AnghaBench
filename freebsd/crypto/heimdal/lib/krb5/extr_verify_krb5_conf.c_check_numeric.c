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
 long LONG_MAX ; 
 long LONG_MIN ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_numeric(krb5_context context, const char *path, char *data)
{
    long v;
    char *end;
    v = strtol(data, &end, 0);

    if ((v == LONG_MIN || v == LONG_MAX) && errno != 0) {
	krb5_warnx(context, "%s: over/under flow for \"%s\"",
		   path, data);
	return 1;
    }
    if(*end != '\0') {
	krb5_warnx(context, "%s: failed to parse \"%s\" as a number",
		   path, data);
	return 1;
    }
    return 0;
}