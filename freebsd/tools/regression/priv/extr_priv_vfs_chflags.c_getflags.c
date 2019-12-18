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
typedef  int /*<<< orphan*/  u_long ;
struct stat {int /*<<< orphan*/  st_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static u_long
getflags(char *fpathp)
{
	struct stat sb;

	if (stat(fpathp, &sb) < 0)
		err(-1, "stat(%s)", fpathp);

	return (sb.st_flags);
}