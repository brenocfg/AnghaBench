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
struct statvfs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 struct statvfs* allstatvfs ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 struct statvfs* realloc (struct statvfs*,int) ; 
 int sftotal ; 
 int sfused ; 

struct statvfs *
getnewstatvfs(void)
{

	if (sftotal == sfused) {
		sftotal = sftotal ? sftotal * 2 : 1;
		allstatvfs = realloc(allstatvfs,
		    sftotal * sizeof(struct statvfs));
		if (allstatvfs == NULL)
			err(EXIT_FAILURE, "realloc");
	}

	return (&allstatvfs[sfused++]);
}