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
struct string_list {int dummy; } ;
struct strbuf {int dummy; } ;
struct remote {int url_nr; char const** url; int pushurl_nr; char** pushurl; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/ * util; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 void* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 TYPE_1__* string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_one_entry(struct remote *remote, void *priv)
{
	struct string_list *list = priv;
	struct strbuf url_buf = STRBUF_INIT;
	const char **url;
	int i, url_nr;

	if (remote->url_nr > 0) {
		strbuf_addf(&url_buf, "%s (fetch)", remote->url[0]);
		string_list_append(list, remote->name)->util =
				strbuf_detach(&url_buf, NULL);
	} else
		string_list_append(list, remote->name)->util = NULL;
	if (remote->pushurl_nr) {
		url = remote->pushurl;
		url_nr = remote->pushurl_nr;
	} else {
		url = remote->url;
		url_nr = remote->url_nr;
	}
	for (i = 0; i < url_nr; i++)
	{
		strbuf_addf(&url_buf, "%s (push)", url[i]);
		string_list_append(list, remote->name)->util =
				strbuf_detach(&url_buf, NULL);
	}

	return 0;
}