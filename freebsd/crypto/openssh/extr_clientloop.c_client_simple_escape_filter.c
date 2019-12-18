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
struct ssh {int dummy; } ;
struct TYPE_4__ {scalar_t__ extended_usage; int /*<<< orphan*/  extended; int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 scalar_t__ CHAN_EXTENDED_WRITE ; 
 int process_escapes (struct ssh*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int
client_simple_escape_filter(struct ssh *ssh, Channel *c, char *buf, int len)
{
	if (c->extended_usage != CHAN_EXTENDED_WRITE)
		return 0;

	return process_escapes(ssh, c, c->input, c->output, c->extended,
	    buf, len);
}