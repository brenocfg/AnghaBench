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
 int /*<<< orphan*/  CHECK_ENV (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch ; 
 int /*<<< orphan*/  buildid ; 
 int /*<<< orphan*/  hostname ; 
 int /*<<< orphan*/  ident ; 
 int /*<<< orphan*/  kernvers ; 
 int /*<<< orphan*/  platform ; 
 int /*<<< orphan*/  release ; 
 int /*<<< orphan*/  sysname ; 
 int /*<<< orphan*/  uservers ; 
 int /*<<< orphan*/  version ; 

__attribute__((used)) static void
setup_get(void)
{
	CHECK_ENV("s", sysname);
	CHECK_ENV("n", hostname);
	CHECK_ENV("r", release);
	CHECK_ENV("v", version);
	CHECK_ENV("m", platform);
	CHECK_ENV("p", arch);
	CHECK_ENV("i", ident);
	CHECK_ENV("K", kernvers);
	CHECK_ENV("U", uservers);
	CHECK_ENV("b", buildid);
}