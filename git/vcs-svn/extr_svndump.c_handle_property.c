#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct strbuf {char* buf; size_t len; } ;
struct TYPE_4__ {int type; } ;
struct TYPE_3__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  author; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int S_IFLNK ; 
 int S_IFREG ; 
 int /*<<< orphan*/  constcmp (char const*,char*) ; 
 int /*<<< orphan*/  die (char*) ; 
 TYPE_2__ node_ctx ; 
 int /*<<< orphan*/  parse_date_basic (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ rev_ctx ; 
 int /*<<< orphan*/  strbuf_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_swap (int /*<<< orphan*/ *,struct strbuf*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  warning (char*,char*) ; 

__attribute__((used)) static void handle_property(const struct strbuf *key_buf,
				struct strbuf *val,
				uint32_t *type_set)
{
	const char *key = key_buf->buf;
	size_t keylen = key_buf->len;

	switch (keylen + 1) {
	case sizeof("svn:log"):
		if (constcmp(key, "svn:log"))
			break;
		if (!val)
			die("invalid dump: unsets svn:log");
		strbuf_swap(&rev_ctx.log, val);
		break;
	case sizeof("svn:author"):
		if (constcmp(key, "svn:author"))
			break;
		if (!val)
			strbuf_reset(&rev_ctx.author);
		else
			strbuf_swap(&rev_ctx.author, val);
		break;
	case sizeof("svn:date"):
		if (constcmp(key, "svn:date"))
			break;
		if (!val)
			die("invalid dump: unsets svn:date");
		if (parse_date_basic(val->buf, &rev_ctx.timestamp, NULL))
			warning("invalid timestamp: %s", val->buf);
		break;
	case sizeof("svn:executable"):
	case sizeof("svn:special"):
		if (keylen == strlen("svn:executable") &&
		    constcmp(key, "svn:executable"))
			break;
		if (keylen == strlen("svn:special") &&
		    constcmp(key, "svn:special"))
			break;
		if (*type_set) {
			if (!val)
				return;
			die("invalid dump: sets type twice");
		}
		if (!val) {
			node_ctx.type = S_IFREG | 0644;
			return;
		}
		*type_set = 1;
		node_ctx.type = keylen == strlen("svn:executable") ?
				(S_IFREG | 0755) :
				S_IFLNK;
	}
}