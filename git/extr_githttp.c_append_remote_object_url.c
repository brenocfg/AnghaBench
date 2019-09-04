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
 int /*<<< orphan*/  end_url_with_slash (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 

void append_remote_object_url(struct strbuf *buf, const char *url,
			      const char *hex,
			      int only_two_digit_prefix)
{
	end_url_with_slash(buf, url);

	strbuf_addf(buf, "objects/%.*s/", 2, hex);
	if (!only_two_digit_prefix)
		strbuf_addstr(buf, hex + 2);
}