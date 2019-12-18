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
struct xinpgen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 struct xinpgen* malloc (size_t) ; 
 int sysctlbyname (char const*,struct xinpgen*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xinpgen *
getxpcblist(const char *name)
{
	struct xinpgen *xinp;
	size_t len;
	int rv;

	len = 0;
	rv = sysctlbyname(name, NULL, &len, NULL, 0);
	if (rv == -1)
		err(1, "sysctlbyname %s", name);

	if (len == 0)
		errx(1, "%s is empty", name);

	xinp = malloc(len);
	if (xinp == NULL)
		errx(1, "malloc failed");

	rv = sysctlbyname(name, xinp, &len, NULL, 0);
	if (rv == -1)
		err(1, "sysctlbyname %s", name);

	return (xinp);
}