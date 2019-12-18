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
struct transport {char const* url; TYPE_1__* smart_options; int /*<<< orphan*/ * vtable; struct git_transport_data* data; struct remote* remote; scalar_t__ got_remote_refs; int /*<<< orphan*/  progress; } ;
struct remote {char* foreign_vcs; char** url; char* uploadpack; char* receivepack; } ;
struct TYPE_2__ {int thin; char* uploadpack; char* receivepack; } ;
struct git_transport_data {scalar_t__ got_remote_heads; int /*<<< orphan*/ * conn; TYPE_1__ options; } ;
struct bundle_transport_data {scalar_t__ got_remote_heads; int /*<<< orphan*/ * conn; TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  builtin_smart_vtable ; 
 int /*<<< orphan*/  bundle_vtable ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int external_specification_len (char const*) ; 
 scalar_t__ is_bundle (char const*,int) ; 
 scalar_t__ is_file (char const*) ; 
 int /*<<< orphan*/  is_url (char const*) ; 
 scalar_t__ is_urlschemechar (int,char const) ; 
 int /*<<< orphan*/  isatty (int) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  transport_check_allowed (char*) ; 
 int /*<<< orphan*/  transport_helper_init (struct transport*,char const*) ; 
 scalar_t__ url_is_local_not_ssh (char const*) ; 
 void* xcalloc (int,int) ; 
 char* xmemdupz (char const*,int) ; 
 char* xstrndup (char const*,int) ; 

struct transport *transport_get(struct remote *remote, const char *url)
{
	const char *helper;
	struct transport *ret = xcalloc(1, sizeof(*ret));

	ret->progress = isatty(2);

	if (!remote)
		BUG("No remote provided to transport_get()");

	ret->got_remote_refs = 0;
	ret->remote = remote;
	helper = remote->foreign_vcs;

	if (!url && remote->url)
		url = remote->url[0];
	ret->url = url;

	/* maybe it is a foreign URL? */
	if (url) {
		const char *p = url;

		while (is_urlschemechar(p == url, *p))
			p++;
		if (starts_with(p, "::"))
			helper = xstrndup(url, p - url);
	}

	if (helper) {
		transport_helper_init(ret, helper);
	} else if (starts_with(url, "rsync:")) {
		die(_("git-over-rsync is no longer supported"));
	} else if (url_is_local_not_ssh(url) && is_file(url) && is_bundle(url, 1)) {
		struct bundle_transport_data *data = xcalloc(1, sizeof(*data));
		transport_check_allowed("file");
		ret->data = data;
		ret->vtable = &bundle_vtable;
		ret->smart_options = NULL;
	} else if (!is_url(url)
		|| starts_with(url, "file://")
		|| starts_with(url, "git://")
		|| starts_with(url, "ssh://")
		|| starts_with(url, "git+ssh://") /* deprecated - do not use */
		|| starts_with(url, "ssh+git://") /* deprecated - do not use */
		) {
		/*
		 * These are builtin smart transports; "allowed" transports
		 * will be checked individually in git_connect.
		 */
		struct git_transport_data *data = xcalloc(1, sizeof(*data));
		ret->data = data;
		ret->vtable = &builtin_smart_vtable;
		ret->smart_options = &(data->options);

		data->conn = NULL;
		data->got_remote_heads = 0;
	} else {
		/* Unknown protocol in URL. Pass to external handler. */
		int len = external_specification_len(url);
		char *handler = xmemdupz(url, len);
		transport_helper_init(ret, handler);
	}

	if (ret->smart_options) {
		ret->smart_options->thin = 1;
		ret->smart_options->uploadpack = "git-upload-pack";
		if (remote->uploadpack)
			ret->smart_options->uploadpack = remote->uploadpack;
		ret->smart_options->receivepack = "git-receive-pack";
		if (remote->receivepack)
			ret->smart_options->receivepack = remote->receivepack;
	}

	return ret;
}