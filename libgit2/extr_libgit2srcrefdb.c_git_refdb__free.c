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
typedef  int /*<<< orphan*/  git_refdb ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  refdb_free_backend (int /*<<< orphan*/ *) ; 

void git_refdb__free(git_refdb *db)
{
	refdb_free_backend(db);
	git__memzero(db, sizeof(*db));
	git__free(db);
}