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
 int parse_time (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
check_time(krb5_context context, const char *path, char *data)
{
    if(parse_time(data, NULL) == -1) {
	krb5_warnx(context, "%s: failed to parse \"%s\" as time", path, data);
	return 1;
    }
    return 0;
}