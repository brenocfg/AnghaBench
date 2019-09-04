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
 int get_one_line (char const*) ; 
 int /*<<< orphan*/  is_blank_line (char const*,int*) ; 

const char *skip_blank_lines(const char *msg)
{
	for (;;) {
		int linelen = get_one_line(msg);
		int ll = linelen;
		if (!linelen)
			break;
		if (!is_blank_line(msg, &ll))
			break;
		msg += linelen;
	}
	return msg;
}