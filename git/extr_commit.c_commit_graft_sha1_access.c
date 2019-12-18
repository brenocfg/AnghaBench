#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char const* hash; } ;
struct commit_graft {TYPE_1__ oid; } ;

/* Variables and functions */

__attribute__((used)) static const unsigned char *commit_graft_sha1_access(size_t index, void *table)
{
	struct commit_graft **commit_graft_table = table;
	return commit_graft_table[index]->oid.hash;
}