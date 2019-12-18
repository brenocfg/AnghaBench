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
struct transport {struct string_list const* push_options; } ;
struct string_list {scalar_t__ nr; } ;
struct refspec {scalar_t__ nr; } ;
struct remote {struct refspec push; } ;

/* Variables and functions */
 int TRANSPORT_PUSH_ALL ; 
 int TRANSPORT_PUSH_MIRROR ; 
 int TRANSPORT_PUSH_OPTIONS ; 
 int push_url_of_remote (struct remote*,char const***) ; 
 scalar_t__ push_with_options (struct transport*,struct refspec*,int) ; 
 struct refspec rs ; 
 int /*<<< orphan*/  setup_default_push_refspecs (struct remote*) ; 
 struct transport* transport_get (struct remote*,char const*) ; 

__attribute__((used)) static int do_push(const char *repo, int flags,
		   const struct string_list *push_options,
		   struct remote *remote)
{
	int i, errs;
	const char **url;
	int url_nr;
	struct refspec *push_refspec = &rs;

	if (push_options->nr)
		flags |= TRANSPORT_PUSH_OPTIONS;

	if (!push_refspec->nr && !(flags & TRANSPORT_PUSH_ALL)) {
		if (remote->push.nr) {
			push_refspec = &remote->push;
		} else if (!(flags & TRANSPORT_PUSH_MIRROR))
			setup_default_push_refspecs(remote);
	}
	errs = 0;
	url_nr = push_url_of_remote(remote, &url);
	if (url_nr) {
		for (i = 0; i < url_nr; i++) {
			struct transport *transport =
				transport_get(remote, url[i]);
			if (flags & TRANSPORT_PUSH_OPTIONS)
				transport->push_options = push_options;
			if (push_with_options(transport, push_refspec, flags))
				errs++;
		}
	} else {
		struct transport *transport =
			transport_get(remote, NULL);
		if (flags & TRANSPORT_PUSH_OPTIONS)
			transport->push_options = push_options;
		if (push_with_options(transport, push_refspec, flags))
			errs++;
	}
	return !!errs;
}