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
typedef  char* uint8_t ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 
 int strlen (char*) ; 

void
smp_command_decode(uint8_t *smp_request, int request_len, struct sbuf *sb,
		   char *line_prefix, int first_line_len, int line_len)
{
	int i, cur_len;

	for (i = 0, cur_len = first_line_len; i < request_len; i++) {
		/*
		 * Each byte takes 3 characters.  As soon as we go less
		 * than 6 (meaning we have at least 3 and at most 5
		 * characters left), check to see whether the subsequent
		 * line length (line_len) is long enough to bother with.
		 * If the user set it to 0, or some other length that isn't
		 * enough to hold at least the prefix and one byte, put ...
		 * on the first line to indicate that there is more data
		 * and bail out.
		 */
		if ((cur_len < 6)
		 && (line_len < (strlen(line_prefix) + 3))) {
			sbuf_printf(sb, "...");
			return;
		}
		if (cur_len < 3) {
			sbuf_printf(sb, "\n%s", line_prefix);
			cur_len = line_len - strlen(line_prefix);
		}
		sbuf_printf(sb, "%02x ", smp_request[i]);
		cur_len = cur_len - 3;
	}
}