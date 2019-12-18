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
typedef  int /*<<< orphan*/  git_oidmap ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kh_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid ; 

int git_oidmap_new(git_oidmap **out)
{
	*out = kh_init(oid);
	GIT_ERROR_CHECK_ALLOC(*out);

	return 0;
}