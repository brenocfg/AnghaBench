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
struct thread {scalar_t__ td_intr_nesting_level; struct kcov_info* td_kcov_info; int /*<<< orphan*/ * td_intr_frame; } ;
struct kcov_info {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ KCOV_STATE_RUNNING ; 
 scalar_t__ atomic_load_acq_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct kcov_info *
get_kinfo(struct thread *td)
{
	struct kcov_info *info;

	/* We might have a NULL thread when releasing the secondary CPUs */
	if (td == NULL)
		return (NULL);

	/*
	 * We are in an interrupt, stop tracing as it is not explicitly
	 * part of a syscall.
	 */
	if (td->td_intr_nesting_level > 0 || td->td_intr_frame != NULL)
		return (NULL);

	/*
	 * If info is NULL or the state is not running we are not tracing.
	 */
	info = td->td_kcov_info;
	if (info == NULL ||
	    atomic_load_acq_int(&info->state) != KCOV_STATE_RUNNING)
		return (NULL);

	return (info);
}