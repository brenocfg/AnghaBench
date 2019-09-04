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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct remote_lock {int /*<<< orphan*/  timeout; int /*<<< orphan*/  token; } ;
struct curl_slist {int dummy; } ;
typedef  enum dav_header_flag { ____Placeholder_dav_header_flag } dav_header_flag ;

/* Variables and functions */
 int DAV_HEADER_IF ; 
 int DAV_HEADER_LOCK ; 
 int DAV_HEADER_TIMEOUT ; 
 struct strbuf STRBUF_INIT ; 
 struct curl_slist* curl_slist_append (struct curl_slist*,int /*<<< orphan*/ ) ; 
 struct curl_slist* http_copy_default_headers () ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static struct curl_slist *get_dav_token_headers(struct remote_lock *lock, enum dav_header_flag options)
{
	struct strbuf buf = STRBUF_INIT;
	struct curl_slist *dav_headers = http_copy_default_headers();

	if (options & DAV_HEADER_IF) {
		strbuf_addf(&buf, "If: (<%s>)", lock->token);
		dav_headers = curl_slist_append(dav_headers, buf.buf);
		strbuf_reset(&buf);
	}
	if (options & DAV_HEADER_LOCK) {
		strbuf_addf(&buf, "Lock-Token: <%s>", lock->token);
		dav_headers = curl_slist_append(dav_headers, buf.buf);
		strbuf_reset(&buf);
	}
	if (options & DAV_HEADER_TIMEOUT) {
		strbuf_addf(&buf, "Timeout: Second-%ld", lock->timeout);
		dav_headers = curl_slist_append(dav_headers, buf.buf);
		strbuf_reset(&buf);
	}
	strbuf_release(&buf);

	return dav_headers;
}