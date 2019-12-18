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
struct diff_filespec {scalar_t__ mode; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_null_oid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is_valid(const struct diff_filespec *dfs)
{
	return dfs->mode != 0 && !is_null_oid(&dfs->oid);
}