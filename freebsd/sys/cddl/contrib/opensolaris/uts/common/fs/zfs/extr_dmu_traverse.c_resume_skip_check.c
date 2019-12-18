#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
struct TYPE_3__ {int td_flags; int /*<<< orphan*/ * td_resume; } ;
typedef  TYPE_1__ traverse_data_t ;
typedef  int /*<<< orphan*/  resume_skip_t ;
typedef  int /*<<< orphan*/  dnode_phys_t ;

/* Variables and functions */
 int /*<<< orphan*/  RESUME_SKIP_ALL ; 
 int /*<<< orphan*/  RESUME_SKIP_CHILDREN ; 
 int /*<<< orphan*/  RESUME_SKIP_NONE ; 
 int TRAVERSE_POST ; 
 int /*<<< orphan*/  ZB_IS_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ bcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ zbookmark_subtree_completed (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static resume_skip_t
resume_skip_check(traverse_data_t *td, const dnode_phys_t *dnp,
    const zbookmark_phys_t *zb)
{
	if (td->td_resume != NULL && !ZB_IS_ZERO(td->td_resume)) {
		/*
		 * If we already visited this bp & everything below,
		 * don't bother doing it again.
		 */
		if (zbookmark_subtree_completed(dnp, zb, td->td_resume))
			return (RESUME_SKIP_ALL);

		/*
		 * If we found the block we're trying to resume from, zero
		 * the bookmark out to indicate that we have resumed.
		 */
		if (bcmp(zb, td->td_resume, sizeof (*zb)) == 0) {
			bzero(td->td_resume, sizeof (*zb));
			if (td->td_flags & TRAVERSE_POST)
				return (RESUME_SKIP_CHILDREN);
		}
	}
	return (RESUME_SKIP_NONE);
}