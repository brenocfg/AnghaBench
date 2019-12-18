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
 int /*<<< orphan*/  CI_ENV_MAX_REUSE ; 
 int /*<<< orphan*/  CI_HASH_SIZE ; 
 int CI_INITIAL_MAX_REUSE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _CITRUS_HASH_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int atoi (scalar_t__) ; 
 int /*<<< orphan*/  ci_lock ; 
 scalar_t__ getenv (int /*<<< orphan*/ ) ; 
 int isinit ; 
 int /*<<< orphan*/  issetugid () ; 
 int shared_max_reuse ; 
 int /*<<< orphan*/  shared_pool ; 
 int /*<<< orphan*/  shared_unused ; 

__attribute__((used)) static __inline void
init_cache(void)
{

	WLOCK(&ci_lock);
	if (!isinit) {
		_CITRUS_HASH_INIT(&shared_pool, CI_HASH_SIZE);
		TAILQ_INIT(&shared_unused);
		shared_max_reuse = -1;
		if (!issetugid() && getenv(CI_ENV_MAX_REUSE))
			shared_max_reuse = atoi(getenv(CI_ENV_MAX_REUSE));
		if (shared_max_reuse < 0)
			shared_max_reuse = CI_INITIAL_MAX_REUSE;
		isinit = true;
	}
	UNLOCK(&ci_lock);
}