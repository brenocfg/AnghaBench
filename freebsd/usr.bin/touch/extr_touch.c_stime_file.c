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
struct timespec {int dummy; } ;
struct stat {struct timespec st_mtim; struct timespec st_atim; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static void
stime_file(const char *fname, struct timespec *tsp)
{
	struct stat sb;

	if (stat(fname, &sb))
		err(1, "%s", fname);
	tsp[0] = sb.st_atim;
	tsp[1] = sb.st_mtim;
}