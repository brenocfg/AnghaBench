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
struct _citrus_iconv_shared {scalar_t__ ci_used_count; } ;

/* Variables and functions */
 struct _citrus_iconv_shared* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct _citrus_iconv_shared*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct _citrus_iconv_shared*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _CITRUS_HASH_REMOVE (struct _citrus_iconv_shared*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_hash_entry ; 
 int /*<<< orphan*/  ci_lock ; 
 int /*<<< orphan*/  ci_tailq_entry ; 
 int /*<<< orphan*/  close_shared (struct _citrus_iconv_shared*) ; 
 scalar_t__ shared_max_reuse ; 
 scalar_t__ shared_num_unused ; 
 int /*<<< orphan*/  shared_unused ; 

__attribute__((used)) static void
release_shared(struct _citrus_iconv_shared * __restrict ci)
{

	WLOCK(&ci_lock);
	ci->ci_used_count--;
	if (ci->ci_used_count == 0) {
		/* put it into unused list */
		shared_num_unused++;
		TAILQ_INSERT_TAIL(&shared_unused, ci, ci_tailq_entry);
		/* flood out */
		while (shared_num_unused > shared_max_reuse) {
			ci = TAILQ_FIRST(&shared_unused);
			TAILQ_REMOVE(&shared_unused, ci, ci_tailq_entry);
			_CITRUS_HASH_REMOVE(ci, ci_hash_entry);
			shared_num_unused--;
			close_shared(ci);
		}
	}

	UNLOCK(&ci_lock);
}