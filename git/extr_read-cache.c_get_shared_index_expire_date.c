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
 unsigned long approxidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_get_expiry (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shared_index_expire ; 

__attribute__((used)) static unsigned long get_shared_index_expire_date(void)
{
	static unsigned long shared_index_expire_date;
	static int shared_index_expire_date_prepared;

	if (!shared_index_expire_date_prepared) {
		git_config_get_expiry("splitindex.sharedindexexpire",
				      &shared_index_expire);
		shared_index_expire_date = approxidate(shared_index_expire);
		shared_index_expire_date_prepared = 1;
	}

	return shared_index_expire_date;
}