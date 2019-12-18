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
struct strbuf {int dummy; } ;
struct parallel_fetch_state {int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int fetch_failed_to_start(struct strbuf *out, void *cb, void *task_cb)
{
	struct parallel_fetch_state *state = cb;
	const char *remote = task_cb;

	state->result = error(_("Could not fetch %s"), remote);

	return 0;
}