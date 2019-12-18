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
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_boolean(krb5_context context, const char *path, char *data)
{
    long int v;
    char *end;
    if(strcasecmp(data, "yes") == 0 ||
       strcasecmp(data, "true") == 0 ||
       strcasecmp(data, "no") == 0 ||
       strcasecmp(data, "false") == 0)
	return 0;
    v = strtol(data, &end, 0);
    if(*end != '\0') {
	krb5_warnx(context, "%s: failed to parse \"%s\" as a boolean",
		   path, data);
	return 1;
    }
    if(v != 0 && v != 1)
	krb5_warnx(context, "%s: numeric value \"%s\" is treated as \"true\"",
		   path, data);
    return 0;
}