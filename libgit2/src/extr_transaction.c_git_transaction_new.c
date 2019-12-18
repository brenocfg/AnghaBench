#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * repo; int /*<<< orphan*/  pool; int /*<<< orphan*/  type; int /*<<< orphan*/  db; int /*<<< orphan*/  locks; } ;
typedef  TYPE_1__ git_transaction ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_pool ;

/* Variables and functions */
 int /*<<< orphan*/  TRANSACTION_REFS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_init (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* git_pool_mallocz (int /*<<< orphan*/ *,int) ; 
 int git_repository_refdb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_strmap_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int git_transaction_new(git_transaction **out, git_repository *repo)
{
	int error;
	git_pool pool;
	git_transaction *tx = NULL;

	assert(out && repo);

	git_pool_init(&pool, 1);

	tx = git_pool_mallocz(&pool, sizeof(git_transaction));
	if (!tx) {
		error = -1;
		goto on_error;
	}

	if ((error = git_strmap_new(&tx->locks)) < 0) {
		error = -1;
		goto on_error;
	}

	if ((error = git_repository_refdb(&tx->db, repo)) < 0)
		goto on_error;

	tx->type = TRANSACTION_REFS;
	memcpy(&tx->pool, &pool, sizeof(git_pool));
	tx->repo = repo;
	*out = tx;
	return 0;

on_error:
	git_pool_clear(&pool);
	return error;
}