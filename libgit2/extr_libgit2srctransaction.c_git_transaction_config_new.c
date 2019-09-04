#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * cfg; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_transaction ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  TRANSACTION_CONFIG ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* git__calloc (int,int) ; 

int git_transaction_config_new(git_transaction **out, git_config *cfg)
{
	git_transaction *tx;
	assert(out && cfg);

	tx = git__calloc(1, sizeof(git_transaction));
	GIT_ERROR_CHECK_ALLOC(tx);

	tx->type = TRANSACTION_CONFIG;
	tx->cfg = cfg;
	*out = tx;
	return 0;
}