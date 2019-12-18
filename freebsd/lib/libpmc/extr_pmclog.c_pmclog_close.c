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
struct pmclog_parse_state {struct pmclog_parse_state* ps_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pmclog_parse_state*) ; 

void
pmclog_close(void *cookie)
{
	struct pmclog_parse_state *ps;

	ps = (struct pmclog_parse_state *) cookie;

	if (ps->ps_buffer)
		free(ps->ps_buffer);

	free(ps);
}