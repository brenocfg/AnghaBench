#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct string_list {int dummy; } ;
struct strbuf {int /*<<< orphan*/  len; } ;
struct process_trailer_options {int no_divider; int only_trailers; int unfold; int value_only; struct strbuf* separator; struct string_list* filter_data; int /*<<< orphan*/  filter; } ;
struct TYPE_15__ {int /*<<< orphan*/  len; int /*<<< orphan*/  off; } ;
struct TYPE_14__ {int /*<<< orphan*/  len; int /*<<< orphan*/  off; } ;
struct TYPE_18__ {char result; char const* gpg_output; char const* signer; char const* key; char const* fingerprint; char const* primary_key_fingerprint; } ;
struct format_commit_context {char* message; char const* commit_encoding; int subject_off; int /*<<< orphan*/  body_off; int /*<<< orphan*/  commit_message_parsed; int /*<<< orphan*/  message_off; TYPE_7__* pretty_ctx; TYPE_6__ committer; TYPE_5__ author; int /*<<< orphan*/  commit_header_parsed; TYPE_9__ signature_check; struct commit* commit; int /*<<< orphan*/  auto_color; } ;
struct commit_list {TYPE_3__* item; struct commit_list* next; } ;
struct TYPE_10__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  parsed; } ;
struct commit {struct commit_list* parents; TYPE_1__ object; } ;
struct TYPE_17__ {char* util; } ;
struct TYPE_16__ {char const* notes_message; int /*<<< orphan*/  date_mode; int /*<<< orphan*/  reflog_info; int /*<<< orphan*/  date_mode_explicit; TYPE_4__* rev; int /*<<< orphan*/  abbrev; int /*<<< orphan*/  color; } ;
struct TYPE_13__ {int /*<<< orphan*/  sources; } ;
struct TYPE_11__ {int /*<<< orphan*/  oid; } ;
struct TYPE_12__ {TYPE_2__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_COMMIT ; 
 int /*<<< orphan*/  DIFF_RESET ; 
 char const* GIT_COLOR_RESET ; 
 struct process_trailer_options PROCESS_TRAILER_OPTIONS_INIT ; 
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_NODUP ; 
 int /*<<< orphan*/  check_commit_signature (struct commit*,TYPE_9__*) ; 
 char const* diff_get_color (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_decorations (struct strbuf*,struct commit const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_decorations_extended (struct strbuf*,struct commit const*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 size_t format_person_part (struct strbuf*,char const,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t format_reflog_person (struct strbuf*,char const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_sanitized_subject (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  format_subject (struct strbuf*,char const*,char*) ; 
 int /*<<< orphan*/  format_trailer_match_cb ; 
 int /*<<< orphan*/  format_trailers_from_commit (struct strbuf*,char const*,struct process_trailer_options*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * get_commit_tree_oid (struct commit const*) ; 
 int /*<<< orphan*/  get_reflog_message (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_reflog_selector (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char const* get_revision_mark (int /*<<< orphan*/ *,struct commit const*) ; 
 scalar_t__ match_placeholder_arg_value (char const*,char*,char const**,char const**,size_t*) ; 
 int /*<<< orphan*/  match_placeholder_bool_arg (char const*,char*,char const**,int*) ; 
 char const* oid_to_hex (int /*<<< orphan*/ *) ; 
 int parse_color (struct strbuf*,char const*,struct format_commit_context*) ; 
 int /*<<< orphan*/  parse_commit_header (struct format_commit_context*) ; 
 int /*<<< orphan*/  parse_commit_message (struct format_commit_context*) ; 
 int /*<<< orphan*/  parse_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t parse_padding_placeholder (char const*,struct format_commit_context*) ; 
 char** revision_sources_at (int /*<<< orphan*/ ,struct commit const*) ; 
 int /*<<< orphan*/  rewrap_message_tail (struct strbuf*,struct format_commit_context*,unsigned long,unsigned long,unsigned long) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strbuf_add_unique_abbrev (struct strbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_expand (struct strbuf*,char*,size_t (*) (struct strbuf*,char const*,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 size_t strbuf_expand_literal_cb (struct strbuf*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 char* strchr (char const*,char) ; 
 TYPE_8__* string_list_append (struct string_list*,char const*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 unsigned long strtoul (char const*,char**,int) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  want_color (int /*<<< orphan*/ ) ; 
 char* xstrndup (char const*,size_t) ; 

__attribute__((used)) static size_t format_commit_one(struct strbuf *sb, /* in UTF-8 */
				const char *placeholder,
				void *context)
{
	struct format_commit_context *c = context;
	const struct commit *commit = c->commit;
	const char *msg = c->message;
	struct commit_list *p;
	const char *arg;
	size_t res;
	char **slot;

	/* these are independent of the commit */
	res = strbuf_expand_literal_cb(sb, placeholder, NULL);
	if (res)
		return res;

	switch (placeholder[0]) {
	case 'C':
		if (starts_with(placeholder + 1, "(auto)")) {
			c->auto_color = want_color(c->pretty_ctx->color);
			if (c->auto_color && sb->len)
				strbuf_addstr(sb, GIT_COLOR_RESET);
			return 7; /* consumed 7 bytes, "C(auto)" */
		} else {
			int ret = parse_color(sb, placeholder, c);
			if (ret)
				c->auto_color = 0;
			/*
			 * Otherwise, we decided to treat %C<unknown>
			 * as a literal string, and the previous
			 * %C(auto) is still valid.
			 */
			return ret;
		}
	case 'w':
		if (placeholder[1] == '(') {
			unsigned long width = 0, indent1 = 0, indent2 = 0;
			char *next;
			const char *start = placeholder + 2;
			const char *end = strchr(start, ')');
			if (!end)
				return 0;
			if (end > start) {
				width = strtoul(start, &next, 10);
				if (*next == ',') {
					indent1 = strtoul(next + 1, &next, 10);
					if (*next == ',') {
						indent2 = strtoul(next + 1,
								 &next, 10);
					}
				}
				if (*next != ')')
					return 0;
			}
			rewrap_message_tail(sb, c, width, indent1, indent2);
			return end - placeholder + 1;
		} else
			return 0;

	case '<':
	case '>':
		return parse_padding_placeholder(placeholder, c);
	}

	/* these depend on the commit */
	if (!commit->object.parsed)
		parse_object(the_repository, &commit->object.oid);

	switch (placeholder[0]) {
	case 'H':		/* commit hash */
		strbuf_addstr(sb, diff_get_color(c->auto_color, DIFF_COMMIT));
		strbuf_addstr(sb, oid_to_hex(&commit->object.oid));
		strbuf_addstr(sb, diff_get_color(c->auto_color, DIFF_RESET));
		return 1;
	case 'h':		/* abbreviated commit hash */
		strbuf_addstr(sb, diff_get_color(c->auto_color, DIFF_COMMIT));
		strbuf_add_unique_abbrev(sb, &commit->object.oid,
					 c->pretty_ctx->abbrev);
		strbuf_addstr(sb, diff_get_color(c->auto_color, DIFF_RESET));
		return 1;
	case 'T':		/* tree hash */
		strbuf_addstr(sb, oid_to_hex(get_commit_tree_oid(commit)));
		return 1;
	case 't':		/* abbreviated tree hash */
		strbuf_add_unique_abbrev(sb,
					 get_commit_tree_oid(commit),
					 c->pretty_ctx->abbrev);
		return 1;
	case 'P':		/* parent hashes */
		for (p = commit->parents; p; p = p->next) {
			if (p != commit->parents)
				strbuf_addch(sb, ' ');
			strbuf_addstr(sb, oid_to_hex(&p->item->object.oid));
		}
		return 1;
	case 'p':		/* abbreviated parent hashes */
		for (p = commit->parents; p; p = p->next) {
			if (p != commit->parents)
				strbuf_addch(sb, ' ');
			strbuf_add_unique_abbrev(sb, &p->item->object.oid,
						 c->pretty_ctx->abbrev);
		}
		return 1;
	case 'm':		/* left/right/bottom */
		strbuf_addstr(sb, get_revision_mark(NULL, commit));
		return 1;
	case 'd':
		format_decorations(sb, commit, c->auto_color);
		return 1;
	case 'D':
		format_decorations_extended(sb, commit, c->auto_color, "", ", ", "");
		return 1;
	case 'S':		/* tag/branch like --source */
		if (!(c->pretty_ctx->rev && c->pretty_ctx->rev->sources))
			return 0;
		slot = revision_sources_at(c->pretty_ctx->rev->sources, commit);
		if (!(slot && *slot))
			return 0;
		strbuf_addstr(sb, *slot);
		return 1;
	case 'g':		/* reflog info */
		switch(placeholder[1]) {
		case 'd':	/* reflog selector */
		case 'D':
			if (c->pretty_ctx->reflog_info)
				get_reflog_selector(sb,
						    c->pretty_ctx->reflog_info,
						    &c->pretty_ctx->date_mode,
						    c->pretty_ctx->date_mode_explicit,
						    (placeholder[1] == 'd'));
			return 2;
		case 's':	/* reflog message */
			if (c->pretty_ctx->reflog_info)
				get_reflog_message(sb, c->pretty_ctx->reflog_info);
			return 2;
		case 'n':
		case 'N':
		case 'e':
		case 'E':
			return format_reflog_person(sb,
						    placeholder[1],
						    c->pretty_ctx->reflog_info,
						    &c->pretty_ctx->date_mode);
		}
		return 0;	/* unknown %g placeholder */
	case 'N':
		if (c->pretty_ctx->notes_message) {
			strbuf_addstr(sb, c->pretty_ctx->notes_message);
			return 1;
		}
		return 0;
	}

	if (placeholder[0] == 'G') {
		if (!c->signature_check.result)
			check_commit_signature(c->commit, &(c->signature_check));
		switch (placeholder[1]) {
		case 'G':
			if (c->signature_check.gpg_output)
				strbuf_addstr(sb, c->signature_check.gpg_output);
			break;
		case '?':
			switch (c->signature_check.result) {
			case 'G':
			case 'B':
			case 'E':
			case 'U':
			case 'N':
			case 'X':
			case 'Y':
			case 'R':
				strbuf_addch(sb, c->signature_check.result);
			}
			break;
		case 'S':
			if (c->signature_check.signer)
				strbuf_addstr(sb, c->signature_check.signer);
			break;
		case 'K':
			if (c->signature_check.key)
				strbuf_addstr(sb, c->signature_check.key);
			break;
		case 'F':
			if (c->signature_check.fingerprint)
				strbuf_addstr(sb, c->signature_check.fingerprint);
			break;
		case 'P':
			if (c->signature_check.primary_key_fingerprint)
				strbuf_addstr(sb, c->signature_check.primary_key_fingerprint);
			break;
		default:
			return 0;
		}
		return 2;
	}


	/* For the rest we have to parse the commit header. */
	if (!c->commit_header_parsed)
		parse_commit_header(c);

	switch (placeholder[0]) {
	case 'a':	/* author ... */
		return format_person_part(sb, placeholder[1],
				   msg + c->author.off, c->author.len,
				   &c->pretty_ctx->date_mode);
	case 'c':	/* committer ... */
		return format_person_part(sb, placeholder[1],
				   msg + c->committer.off, c->committer.len,
				   &c->pretty_ctx->date_mode);
	case 'e':	/* encoding */
		if (c->commit_encoding)
			strbuf_addstr(sb, c->commit_encoding);
		return 1;
	case 'B':	/* raw body */
		/* message_off is always left at the initial newline */
		strbuf_addstr(sb, msg + c->message_off + 1);
		return 1;
	}

	/* Now we need to parse the commit message. */
	if (!c->commit_message_parsed)
		parse_commit_message(c);

	switch (placeholder[0]) {
	case 's':	/* subject */
		format_subject(sb, msg + c->subject_off, " ");
		return 1;
	case 'f':	/* sanitized subject */
		format_sanitized_subject(sb, msg + c->subject_off);
		return 1;
	case 'b':	/* body */
		strbuf_addstr(sb, msg + c->body_off);
		return 1;
	}

	if (skip_prefix(placeholder, "(trailers", &arg)) {
		struct process_trailer_options opts = PROCESS_TRAILER_OPTIONS_INIT;
		struct string_list filter_list = STRING_LIST_INIT_NODUP;
		struct strbuf sepbuf = STRBUF_INIT;
		size_t ret = 0;

		opts.no_divider = 1;

		if (*arg == ':') {
			arg++;
			for (;;) {
				const char *argval;
				size_t arglen;

				if (match_placeholder_arg_value(arg, "key", &arg, &argval, &arglen)) {
					uintptr_t len = arglen;

					if (!argval)
						goto trailer_out;

					if (len && argval[len - 1] == ':')
						len--;
					string_list_append(&filter_list, argval)->util = (char *)len;

					opts.filter = format_trailer_match_cb;
					opts.filter_data = &filter_list;
					opts.only_trailers = 1;
				} else if (match_placeholder_arg_value(arg, "separator", &arg, &argval, &arglen)) {
					char *fmt;

					strbuf_reset(&sepbuf);
					fmt = xstrndup(argval, arglen);
					strbuf_expand(&sepbuf, fmt, strbuf_expand_literal_cb, NULL);
					free(fmt);
					opts.separator = &sepbuf;
				} else if (!match_placeholder_bool_arg(arg, "only", &arg, &opts.only_trailers) &&
					   !match_placeholder_bool_arg(arg, "unfold", &arg, &opts.unfold) &&
					   !match_placeholder_bool_arg(arg, "valueonly", &arg, &opts.value_only))
					break;
			}
		}
		if (*arg == ')') {
			format_trailers_from_commit(sb, msg + c->subject_off, &opts);
			ret = arg - placeholder + 1;
		}
	trailer_out:
		string_list_clear(&filter_list, 0);
		strbuf_release(&sepbuf);
		return ret;
	}

	return 0;	/* unknown placeholder */
}