#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int xf_size; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 TYPE_1__* malloc (size_t) ; 
 size_t nxfiles ; 
 TYPE_1__* realloc (TYPE_1__*,size_t) ; 
 int sysctlbyname (char*,TYPE_1__*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* xfiles ; 

__attribute__((used)) static void
getfiles(void)
{
	size_t len, olen;

	olen = len = sizeof(*xfiles);
	if ((xfiles = malloc(len)) == NULL)
		err(1, "malloc()");
	while (sysctlbyname("kern.file", xfiles, &len, 0, 0) == -1) {
		if (errno != ENOMEM || len != olen)
			err(1, "sysctlbyname()");
		olen = len *= 2;
		if ((xfiles = realloc(xfiles, len)) == NULL)
			err(1, "realloc()");
	}
	if (len > 0 && xfiles->xf_size != sizeof(*xfiles))
		errx(1, "struct xfile size mismatch");
	nxfiles = len / sizeof(*xfiles);
}