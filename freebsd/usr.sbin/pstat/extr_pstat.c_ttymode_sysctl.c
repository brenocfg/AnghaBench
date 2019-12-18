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
struct xtty {int dummy; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 char* hdr ; 
 struct xtty* malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 struct xtty* realloc (struct xtty*,size_t) ; 
 int sysctlbyname (char*,struct xtty*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttyprt (struct xtty*) ; 

__attribute__((used)) static void
ttymode_sysctl(void)
{
	struct xtty *xttys;
	size_t len;
	unsigned int i, n;

	(void)printf("%s", hdr);
	if ((xttys = malloc(len = sizeof(*xttys))) == NULL)
		err(1, "malloc()");
	while (sysctlbyname("kern.ttys", xttys, &len, 0, 0) == -1) {
		if (errno != ENOMEM)
			err(1, "sysctlbyname()");
		len *= 2;
		if ((xttys = realloc(xttys, len)) == NULL)
			err(1, "realloc()");
	}
	n = len / sizeof(*xttys);
	for (i = 0; i < n; i++)
		ttyprt(&xttys[i]);
}