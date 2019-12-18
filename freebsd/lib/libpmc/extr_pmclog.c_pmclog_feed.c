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
struct pmclog_parse_state {int ps_len; char* ps_data; scalar_t__ ps_buffer; } ;

/* Variables and functions */

int
pmclog_feed(void *cookie, char *data, int len)
{
	struct pmclog_parse_state *ps;

	ps = (struct pmclog_parse_state *) cookie;

	if (len < 0 ||		/* invalid length */
	    ps->ps_buffer ||	/* called for a file parser */
	    ps->ps_len != 0)	/* unnecessary call */
		return -1;

	ps->ps_data = data;
	ps->ps_len  = len;

	return 0;
}