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
struct string_list {int dummy; } ;
struct strbuf {char const* buf; } ;
struct http_get_options {int initial_request; int no_cache; struct string_list* extra_headers; TYPE_1__* base_url; struct strbuf* effective_url; struct strbuf* charset; struct strbuf* content_type; } ;
struct discovery {char const* service; int /*<<< orphan*/  refs; scalar_t__ proto_git; int /*<<< orphan*/  buf_alloc; int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  http_options ;
typedef  enum protocol_version { ____Placeholder_protocol_version } protocol_version ;
struct TYPE_4__ {scalar_t__ verbosity; } ;
struct TYPE_3__ {char const* buf; } ;

/* Variables and functions */
#define  HTTP_MISSING_TARGET 130 
#define  HTTP_NOAUTH 129 
#define  HTTP_OK 128 
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  check_smart_http (struct discovery*,char const*,struct strbuf*) ; 
 int /*<<< orphan*/  curl_errorstr ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_discovery (struct discovery*) ; 
 scalar_t__ get_protocol_http_header (int,struct strbuf*) ; 
 int get_protocol_version_config () ; 
 scalar_t__ git_env_bool (char*,int) ; 
 int http_get_strbuf (char const*,struct strbuf*,struct http_get_options*) ; 
 struct discovery* last_discovery ; 
 int /*<<< orphan*/  memset (struct http_get_options*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ options ; 
 int /*<<< orphan*/  parse_git_refs (struct discovery*,int) ; 
 int /*<<< orphan*/  parse_info_refs (struct discovery*) ; 
 int protocol_v0 ; 
 int protocol_v2 ; 
 int /*<<< orphan*/  show_http_message (struct strbuf*,struct strbuf*,struct strbuf*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char const*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 char* transport_anonymize_url (char const*) ; 
 TYPE_1__ url ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 
 struct discovery* xcalloc (int,int) ; 
 char const* xstrdup (char const*) ; 

__attribute__((used)) static struct discovery *discover_refs(const char *service, int for_push)
{
	struct strbuf type = STRBUF_INIT;
	struct strbuf charset = STRBUF_INIT;
	struct strbuf buffer = STRBUF_INIT;
	struct strbuf refs_url = STRBUF_INIT;
	struct strbuf effective_url = STRBUF_INIT;
	struct strbuf protocol_header = STRBUF_INIT;
	struct string_list extra_headers = STRING_LIST_INIT_DUP;
	struct discovery *last = last_discovery;
	int http_ret, maybe_smart = 0;
	struct http_get_options http_options;
	enum protocol_version version = get_protocol_version_config();

	if (last && !strcmp(service, last->service))
		return last;
	free_discovery(last);

	strbuf_addf(&refs_url, "%sinfo/refs", url.buf);
	if ((starts_with(url.buf, "http://") || starts_with(url.buf, "https://")) &&
	     git_env_bool("GIT_SMART_HTTP", 1)) {
		maybe_smart = 1;
		if (!strchr(url.buf, '?'))
			strbuf_addch(&refs_url, '?');
		else
			strbuf_addch(&refs_url, '&');
		strbuf_addf(&refs_url, "service=%s", service);
	}

	/*
	 * NEEDSWORK: If we are trying to use protocol v2 and we are planning
	 * to perform a push, then fallback to v0 since the client doesn't know
	 * how to push yet using v2.
	 */
	if (version == protocol_v2 && !strcmp("git-receive-pack", service))
		version = protocol_v0;

	/* Add the extra Git-Protocol header */
	if (get_protocol_http_header(version, &protocol_header))
		string_list_append(&extra_headers, protocol_header.buf);

	memset(&http_options, 0, sizeof(http_options));
	http_options.content_type = &type;
	http_options.charset = &charset;
	http_options.effective_url = &effective_url;
	http_options.base_url = &url;
	http_options.extra_headers = &extra_headers;
	http_options.initial_request = 1;
	http_options.no_cache = 1;

	http_ret = http_get_strbuf(refs_url.buf, &buffer, &http_options);
	switch (http_ret) {
	case HTTP_OK:
		break;
	case HTTP_MISSING_TARGET:
		show_http_message(&type, &charset, &buffer);
		die(_("repository '%s' not found"),
		    transport_anonymize_url(url.buf));
	case HTTP_NOAUTH:
		show_http_message(&type, &charset, &buffer);
		die(_("Authentication failed for '%s'"),
		    transport_anonymize_url(url.buf));
	default:
		show_http_message(&type, &charset, &buffer);
		die(_("unable to access '%s': %s"),
		    transport_anonymize_url(url.buf), curl_errorstr);
	}

	if (options.verbosity && !starts_with(refs_url.buf, url.buf)) {
		char *u = transport_anonymize_url(url.buf);
		warning(_("redirecting to %s"), u);
		free(u);
	}

	last= xcalloc(1, sizeof(*last_discovery));
	last->service = xstrdup(service);
	last->buf_alloc = strbuf_detach(&buffer, &last->len);
	last->buf = last->buf_alloc;

	if (maybe_smart)
		check_smart_http(last, service, &type);

	if (last->proto_git)
		last->refs = parse_git_refs(last, for_push);
	else
		last->refs = parse_info_refs(last);

	strbuf_release(&refs_url);
	strbuf_release(&type);
	strbuf_release(&charset);
	strbuf_release(&effective_url);
	strbuf_release(&buffer);
	strbuf_release(&protocol_header);
	string_list_clear(&extra_headers, 0);
	last_discovery = last;
	return last;
}