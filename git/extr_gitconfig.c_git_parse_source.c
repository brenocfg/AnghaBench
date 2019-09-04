#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int len; } ;
struct parse_event_data {struct config_options const* member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct config_options {int error_action; } ;
typedef  int /*<<< orphan*/  config_fn_t ;
struct TYPE_2__ {int origin_type; int default_error_action; int /*<<< orphan*/  name; int /*<<< orphan*/  linenr; scalar_t__ eof; struct strbuf var; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  CONFIG_ERROR_DIE 136 
#define  CONFIG_ERROR_ERROR 135 
#define  CONFIG_ERROR_SILENT 134 
#define  CONFIG_ERROR_UNSET 133 
 int /*<<< orphan*/  CONFIG_EVENT_COMMENT ; 
 int /*<<< orphan*/  CONFIG_EVENT_ENTRY ; 
 int /*<<< orphan*/  CONFIG_EVENT_EOF ; 
 int /*<<< orphan*/  CONFIG_EVENT_ERROR ; 
 int /*<<< orphan*/  CONFIG_EVENT_SECTION ; 
 int /*<<< orphan*/  CONFIG_EVENT_WHITESPACE ; 
#define  CONFIG_ORIGIN_BLOB 132 
#define  CONFIG_ORIGIN_CMDLINE 131 
#define  CONFIG_ORIGIN_FILE 130 
#define  CONFIG_ORIGIN_STDIN 129 
#define  CONFIG_ORIGIN_SUBMODULE_BLOB 128 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* cf ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 scalar_t__ do_event (int /*<<< orphan*/ ,struct parse_event_data*) ; 
 int error (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_base_var (struct strbuf*) ; 
 int get_next_char () ; 
 scalar_t__ get_value (int /*<<< orphan*/ ,void*,struct strbuf*) ; 
 int /*<<< orphan*/  isalpha (int) ; 
 scalar_t__ isspace (int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 char tolower (int) ; 
 char const* utf8_bom ; 
 char* xstrfmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int git_parse_source(config_fn_t fn, void *data,
			    const struct config_options *opts)
{
	int comment = 0;
	int baselen = 0;
	struct strbuf *var = &cf->var;
	int error_return = 0;
	char *error_msg = NULL;

	/* U+FEFF Byte Order Mark in UTF8 */
	const char *bomptr = utf8_bom;

	/* For the parser event callback */
	struct parse_event_data event_data = {
		CONFIG_EVENT_EOF, 0, opts
	};

	for (;;) {
		int c;

		c = get_next_char();
		if (bomptr && *bomptr) {
			/* We are at the file beginning; skip UTF8-encoded BOM
			 * if present. Sane editors won't put this in on their
			 * own, but e.g. Windows Notepad will do it happily. */
			if (c == (*bomptr & 0377)) {
				bomptr++;
				continue;
			} else {
				/* Do not tolerate partial BOM. */
				if (bomptr != utf8_bom)
					break;
				/* No BOM at file beginning. Cool. */
				bomptr = NULL;
			}
		}
		if (c == '\n') {
			if (cf->eof) {
				if (do_event(CONFIG_EVENT_EOF, &event_data) < 0)
					return -1;
				return 0;
			}
			if (do_event(CONFIG_EVENT_WHITESPACE, &event_data) < 0)
				return -1;
			comment = 0;
			continue;
		}
		if (comment)
			continue;
		if (isspace(c)) {
			if (do_event(CONFIG_EVENT_WHITESPACE, &event_data) < 0)
					return -1;
			continue;
		}
		if (c == '#' || c == ';') {
			if (do_event(CONFIG_EVENT_COMMENT, &event_data) < 0)
					return -1;
			comment = 1;
			continue;
		}
		if (c == '[') {
			if (do_event(CONFIG_EVENT_SECTION, &event_data) < 0)
					return -1;

			/* Reset prior to determining a new stem */
			strbuf_reset(var);
			if (get_base_var(var) < 0 || var->len < 1)
				break;
			strbuf_addch(var, '.');
			baselen = var->len;
			continue;
		}
		if (!isalpha(c))
			break;

		if (do_event(CONFIG_EVENT_ENTRY, &event_data) < 0)
			return -1;

		/*
		 * Truncate the var name back to the section header
		 * stem prior to grabbing the suffix part of the name
		 * and the value.
		 */
		strbuf_setlen(var, baselen);
		strbuf_addch(var, tolower(c));
		if (get_value(fn, data, var) < 0)
			break;
	}

	if (do_event(CONFIG_EVENT_ERROR, &event_data) < 0)
		return -1;

	switch (cf->origin_type) {
	case CONFIG_ORIGIN_BLOB:
		error_msg = xstrfmt(_("bad config line %d in blob %s"),
				      cf->linenr, cf->name);
		break;
	case CONFIG_ORIGIN_FILE:
		error_msg = xstrfmt(_("bad config line %d in file %s"),
				      cf->linenr, cf->name);
		break;
	case CONFIG_ORIGIN_STDIN:
		error_msg = xstrfmt(_("bad config line %d in standard input"),
				      cf->linenr);
		break;
	case CONFIG_ORIGIN_SUBMODULE_BLOB:
		error_msg = xstrfmt(_("bad config line %d in submodule-blob %s"),
				       cf->linenr, cf->name);
		break;
	case CONFIG_ORIGIN_CMDLINE:
		error_msg = xstrfmt(_("bad config line %d in command line %s"),
				       cf->linenr, cf->name);
		break;
	default:
		error_msg = xstrfmt(_("bad config line %d in %s"),
				      cf->linenr, cf->name);
	}

	switch (opts && opts->error_action ?
		opts->error_action :
		cf->default_error_action) {
	case CONFIG_ERROR_DIE:
		die("%s", error_msg);
		break;
	case CONFIG_ERROR_ERROR:
		error_return = error("%s", error_msg);
		break;
	case CONFIG_ERROR_SILENT:
		error_return = -1;
		break;
	case CONFIG_ERROR_UNSET:
		BUG("config error action unset");
	}

	free(error_msg);
	return error_return;
}