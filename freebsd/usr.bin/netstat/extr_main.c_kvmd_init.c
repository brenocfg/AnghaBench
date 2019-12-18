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
 int /*<<< orphan*/  O_RDONLY ; 
 int _POSIX2_LINE_MAX ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/ * kvm_openfiles (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * kvmd ; 
 int /*<<< orphan*/  memf ; 
 int /*<<< orphan*/  nlistf ; 
 scalar_t__ setgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 
 int /*<<< orphan*/  xo_warnx (char*,char*) ; 

__attribute__((used)) static int
kvmd_init(void)
{
	char errbuf[_POSIX2_LINE_MAX];

	if (kvmd != NULL)
		return (0);

	kvmd = kvm_openfiles(nlistf, memf, NULL, O_RDONLY, errbuf);
	if (setgid(getgid()) != 0)
		xo_err(-1, "setgid");

	if (kvmd == NULL) {
		xo_warnx("kvm not available: %s", errbuf);
		return (-1);
	}

	return (0);
}