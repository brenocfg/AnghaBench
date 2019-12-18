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
struct strbuf {int /*<<< orphan*/  buf; scalar_t__ len; } ;

/* Variables and functions */
 int packet_read_line_gently (int,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_list_free (struct strbuf**) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 struct strbuf** strbuf_split_str (char*,char,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int subprocess_read_status(int fd, struct strbuf *status)
{
	struct strbuf **pair;
	char *line;
	int len;

	for (;;) {
		len = packet_read_line_gently(fd, NULL, &line);
		if ((len < 0) || !line)
			break;
		pair = strbuf_split_str(line, '=', 2);
		if (pair[0] && pair[0]->len && pair[1]) {
			/* the last "status=<foo>" line wins */
			if (!strcmp(pair[0]->buf, "status=")) {
				strbuf_reset(status);
				strbuf_addbuf(status, pair[1]);
			}
		}
		strbuf_list_free(pair);
	}

	return (len < 0) ? len : 0;
}