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
struct promisor_remote {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int initialized ; 
 int /*<<< orphan*/  promisor_remote_config ; 
 struct promisor_remote* promisor_remote_lookup (scalar_t__,struct promisor_remote**) ; 
 int /*<<< orphan*/  promisor_remote_move_to_tail (struct promisor_remote*,struct promisor_remote*) ; 
 int /*<<< orphan*/  promisor_remote_new (scalar_t__) ; 
 scalar_t__ repository_format_partial_clone ; 

__attribute__((used)) static void promisor_remote_init(void)
{
	if (initialized)
		return;
	initialized = 1;

	git_config(promisor_remote_config, NULL);

	if (repository_format_partial_clone) {
		struct promisor_remote *o, *previous;

		o = promisor_remote_lookup(repository_format_partial_clone,
					   &previous);
		if (o)
			promisor_remote_move_to_tail(o, previous);
		else
			promisor_remote_new(repository_format_partial_clone);
	}
}