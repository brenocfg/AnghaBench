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
 int /*<<< orphan*/  context ; 
 int doit (char*,int) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  local_flag ; 

__attribute__((used)) static int
loadit(int mergep, const char *name, int argc, char **argv)
{
    if(!local_flag) {
	krb5_warnx(context, "%s is only available in local (-l) mode", name);
	return 0;
    }

    return doit(argv[0], mergep);
}