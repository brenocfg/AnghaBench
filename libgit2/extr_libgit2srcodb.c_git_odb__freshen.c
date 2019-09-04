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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_odb_refresh (int /*<<< orphan*/ *) ; 
 int odb_freshen_1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int git_odb__freshen(git_odb *db, const git_oid *id)
{
	assert(db && id);

	if (odb_freshen_1(db, id, false))
		return 1;

	if (!git_odb_refresh(db))
		return odb_freshen_1(db, id, true);

	/* Failed to refresh, hence not found */
	return 0;
}