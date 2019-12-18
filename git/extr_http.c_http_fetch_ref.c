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
struct strbuf {scalar_t__ len; scalar_t__ buf; } ;
struct ref {int /*<<< orphan*/  symref; int /*<<< orphan*/  old_oid; int /*<<< orphan*/  name; } ;
struct http_get_options {int no_cache; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {scalar_t__ hexsz; } ;

/* Variables and functions */
 scalar_t__ HTTP_OK ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_oid_hex (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ http_get_strbuf (char*,struct strbuf*,struct http_get_options*) ; 
 char* quote_ref_url (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ starts_with (scalar_t__,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  xstrdup (scalar_t__) ; 

int http_fetch_ref(const char *base, struct ref *ref)
{
	struct http_get_options options = {0};
	char *url;
	struct strbuf buffer = STRBUF_INIT;
	int ret = -1;

	options.no_cache = 1;

	url = quote_ref_url(base, ref->name);
	if (http_get_strbuf(url, &buffer, &options) == HTTP_OK) {
		strbuf_rtrim(&buffer);
		if (buffer.len == the_hash_algo->hexsz)
			ret = get_oid_hex(buffer.buf, &ref->old_oid);
		else if (starts_with(buffer.buf, "ref: ")) {
			ref->symref = xstrdup(buffer.buf + 5);
			ret = 0;
		}
	}

	strbuf_release(&buffer);
	free(url);
	return ret;
}