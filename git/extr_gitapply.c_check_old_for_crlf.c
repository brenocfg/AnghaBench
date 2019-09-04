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
struct patch {int crlf_in_old; int /*<<< orphan*/  ws_rule; } ;

/* Variables and functions */
 int /*<<< orphan*/  WS_CR_AT_EOL ; 

__attribute__((used)) static void check_old_for_crlf(struct patch *patch, const char *line, int len)
{
	if (len >= 2 && line[len-1] == '\n' && line[len-2] == '\r') {
		patch->ws_rule |= WS_CR_AT_EOL;
		patch->crlf_in_old = 1;
	}
}