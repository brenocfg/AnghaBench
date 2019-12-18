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
struct evhttp_uri {char* path; scalar_t__ fragment; scalar_t__ query; int /*<<< orphan*/  port; int /*<<< orphan*/  userinfo; scalar_t__ host; scalar_t__ scheme; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  URI_ADD_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_add (struct evbuffer*,char*,int) ; 
 int /*<<< orphan*/  evbuffer_add_printf (struct evbuffer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 size_t evbuffer_get_length (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  evbuffer_remove (struct evbuffer*,char*,size_t) ; 
 int /*<<< orphan*/  fragment ; 
 int /*<<< orphan*/  host ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  query ; 
 int /*<<< orphan*/  scheme ; 

char *
evhttp_uri_join(struct evhttp_uri *uri, char *buf, size_t limit)
{
	struct evbuffer *tmp = 0;
	size_t joined_size = 0;
	char *output = NULL;

#define URI_ADD_(f)	evbuffer_add(tmp, uri->f, strlen(uri->f))

	if (!uri || !buf || !limit)
		return NULL;

	tmp = evbuffer_new();
	if (!tmp)
		return NULL;

	if (uri->scheme) {
		URI_ADD_(scheme);
		evbuffer_add(tmp, ":", 1);
	}
	if (uri->host) {
		evbuffer_add(tmp, "//", 2);
		if (uri->userinfo)
			evbuffer_add_printf(tmp,"%s@", uri->userinfo);
		URI_ADD_(host);
		if (uri->port >= 0)
			evbuffer_add_printf(tmp,":%d", uri->port);

		if (uri->path && uri->path[0] != '/' && uri->path[0] != '\0')
			goto err;
	}

	if (uri->path)
		URI_ADD_(path);

	if (uri->query) {
		evbuffer_add(tmp, "?", 1);
		URI_ADD_(query);
	}

	if (uri->fragment) {
		evbuffer_add(tmp, "#", 1);
		URI_ADD_(fragment);
	}

	evbuffer_add(tmp, "\0", 1); /* NUL */

	joined_size = evbuffer_get_length(tmp);

	if (joined_size > limit) {
		/* It doesn't fit. */
		evbuffer_free(tmp);
		return NULL;
	}
       	evbuffer_remove(tmp, buf, joined_size);

	output = buf;
err:
	evbuffer_free(tmp);

	return output;
#undef URI_ADD_
}