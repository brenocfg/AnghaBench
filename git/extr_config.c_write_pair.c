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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct config_store_data {int baselen; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char const) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,...) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  write_in_full (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t write_pair(int fd, const char *key, const char *value,
			  const struct config_store_data *store)
{
	int i;
	ssize_t ret;
	int length = strlen(key + store->baselen + 1);
	const char *quote = "";
	struct strbuf sb = STRBUF_INIT;

	/*
	 * Check to see if the value needs to be surrounded with a dq pair.
	 * Note that problematic characters are always backslash-quoted; this
	 * check is about not losing leading or trailing SP and strings that
	 * follow beginning-of-comment characters (i.e. ';' and '#') by the
	 * configuration parser.
	 */
	if (value[0] == ' ')
		quote = "\"";
	for (i = 0; value[i]; i++)
		if (value[i] == ';' || value[i] == '#')
			quote = "\"";
	if (i && value[i - 1] == ' ')
		quote = "\"";

	strbuf_addf(&sb, "\t%.*s = %s",
		    length, key + store->baselen + 1, quote);

	for (i = 0; value[i]; i++)
		switch (value[i]) {
		case '\n':
			strbuf_addstr(&sb, "\\n");
			break;
		case '\t':
			strbuf_addstr(&sb, "\\t");
			break;
		case '"':
		case '\\':
			strbuf_addch(&sb, '\\');
			/* fallthrough */
		default:
			strbuf_addch(&sb, value[i]);
			break;
		}
	strbuf_addf(&sb, "%s\n", quote);

	ret = write_in_full(fd, sb.buf, sb.len);
	strbuf_release(&sb);

	return ret;
}