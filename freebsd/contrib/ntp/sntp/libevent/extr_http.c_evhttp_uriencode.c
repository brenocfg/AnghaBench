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
struct evbuffer {int dummy; } ;
typedef  scalar_t__ ev_ssize_t ;

/* Variables and functions */
 scalar_t__ CHAR_IS_UNRESERVED (char const) ; 
 int /*<<< orphan*/  evbuffer_add (struct evbuffer*,char const*,int) ; 
 int /*<<< orphan*/  evbuffer_add_printf (struct evbuffer*,char*,unsigned char) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_get_length (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  evbuffer_remove (struct evbuffer*,char*,int /*<<< orphan*/ ) ; 
 char* mm_malloc (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

char *
evhttp_uriencode(const char *uri, ev_ssize_t len, int space_as_plus)
{
	struct evbuffer *buf = evbuffer_new();
	const char *p, *end;
	char *result;

	if (buf == NULL)
		return (NULL);

	if (len >= 0)
		end = uri+len;
	else
		end = uri+strlen(uri);

	for (p = uri; p < end; p++) {
		if (CHAR_IS_UNRESERVED(*p)) {
			evbuffer_add(buf, p, 1);
		} else if (*p == ' ' && space_as_plus) {
			evbuffer_add(buf, "+", 1);
		} else {
			evbuffer_add_printf(buf, "%%%02X", (unsigned char)(*p));
		}
	}
	evbuffer_add(buf, "", 1); /* NUL-terminator. */
	result = mm_malloc(evbuffer_get_length(buf));
	if (result)
		evbuffer_remove(buf, result, evbuffer_get_length(buf));
	evbuffer_free(buf);

	return (result);
}