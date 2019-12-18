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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int /*<<< orphan*/  BFLAG ; 
 int /*<<< orphan*/  IFLAG ; 
 int /*<<< orphan*/  KFLAG ; 
 int /*<<< orphan*/  MFLAG ; 
 int /*<<< orphan*/  NFLAG ; 
 int /*<<< orphan*/  PFLAG ; 
 int /*<<< orphan*/  PRINT_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFLAG ; 
 int /*<<< orphan*/  SFLAG ; 
 int /*<<< orphan*/  UFLAG ; 
 int /*<<< orphan*/  VFLAG ; 
 int /*<<< orphan*/  arch ; 
 int /*<<< orphan*/  buildid ; 
 int /*<<< orphan*/  hostname ; 
 int /*<<< orphan*/  ident ; 
 int /*<<< orphan*/  kernvers ; 
 int /*<<< orphan*/  platform ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  release ; 
 int /*<<< orphan*/  sysname ; 
 int /*<<< orphan*/  uservers ; 
 int /*<<< orphan*/  version ; 

__attribute__((used)) static void
print_uname(u_int flags)
{
	PRINT_FLAG(flags, SFLAG, sysname);
	PRINT_FLAG(flags, NFLAG, hostname);
	PRINT_FLAG(flags, RFLAG, release);
	PRINT_FLAG(flags, VFLAG, version);
	PRINT_FLAG(flags, MFLAG, platform);
	PRINT_FLAG(flags, PFLAG, arch);
	PRINT_FLAG(flags, IFLAG, ident);
	PRINT_FLAG(flags, KFLAG, kernvers);
	PRINT_FLAG(flags, UFLAG, uservers);
	PRINT_FLAG(flags, BFLAG, buildid);
	printf("\n");
}