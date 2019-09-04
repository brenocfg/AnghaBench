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
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 char* url_decode_internal (char const**,int,int /*<<< orphan*/ *,struct strbuf*,int /*<<< orphan*/ ) ; 

char *url_decode_mem(const char *url, int len)
{
	struct strbuf out = STRBUF_INIT;
	const char *colon = memchr(url, ':', len);

	/* Skip protocol part if present */
	if (colon && url < colon) {
		strbuf_add(&out, url, colon - url);
		len -= colon - url;
		url = colon;
	}
	return url_decode_internal(&url, len, NULL, &out, 0);
}