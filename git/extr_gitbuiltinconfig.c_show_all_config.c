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

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* delim ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omit_values ; 
 int /*<<< orphan*/  printf (char*,char const*,char*,...) ; 
 int /*<<< orphan*/  show_config_origin (struct strbuf*) ; 
 scalar_t__ show_origin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  term ; 

__attribute__((used)) static int show_all_config(const char *key_, const char *value_, void *cb)
{
	if (show_origin) {
		struct strbuf buf = STRBUF_INIT;
		show_config_origin(&buf);
		/* Use fwrite as "buf" can contain \0's if "end_null" is set. */
		fwrite(buf.buf, 1, buf.len, stdout);
		strbuf_release(&buf);
	}
	if (!omit_values && value_)
		printf("%s%c%s%c", key_, delim, value_, term);
	else
		printf("%s%c", key_, term);
	return 0;
}