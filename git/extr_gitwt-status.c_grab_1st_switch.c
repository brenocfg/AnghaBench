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
typedef  int /*<<< orphan*/  timestamp_t ;
struct object_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;
struct grab_1st_switch_cbdata {TYPE_1__ buf; int /*<<< orphan*/  noid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_add (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_add_unique_abbrev (TYPE_1__*,struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (TYPE_1__*) ; 
 char* strchrnul (char const*,char) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static int grab_1st_switch(struct object_id *ooid, struct object_id *noid,
			   const char *email, timestamp_t timestamp, int tz,
			   const char *message, void *cb_data)
{
	struct grab_1st_switch_cbdata *cb = cb_data;
	const char *target = NULL, *end;

	if (!skip_prefix(message, "checkout: moving from ", &message))
		return 0;
	target = strstr(message, " to ");
	if (!target)
		return 0;
	target += strlen(" to ");
	strbuf_reset(&cb->buf);
	oidcpy(&cb->noid, noid);
	end = strchrnul(target, '\n');
	strbuf_add(&cb->buf, target, end - target);
	if (!strcmp(cb->buf.buf, "HEAD")) {
		/* HEAD is relative. Resolve it to the right reflog entry. */
		strbuf_reset(&cb->buf);
		strbuf_add_unique_abbrev(&cb->buf, noid, DEFAULT_ABBREV);
	}
	return 1;
}