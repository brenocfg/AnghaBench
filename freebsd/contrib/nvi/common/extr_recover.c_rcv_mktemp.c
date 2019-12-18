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
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int /*<<< orphan*/  M_SYSERR ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  msgq_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
rcv_mktemp(
	SCR *sp,
	char *path,
	char *dname)
{
	int fd;

	if ((fd = mkstemp(path)) == -1)
		msgq_str(sp, M_SYSERR, dname, "%s");
	return (fd);
}