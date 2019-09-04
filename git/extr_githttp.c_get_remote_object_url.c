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
 int /*<<< orphan*/  append_remote_object_url (struct strbuf*,char const*,char const*,int) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 

char *get_remote_object_url(const char *url, const char *hex,
			    int only_two_digit_prefix)
{
	struct strbuf buf = STRBUF_INIT;
	append_remote_object_url(&buf, url, hex, only_two_digit_prefix);
	return strbuf_detach(&buf, NULL);
}