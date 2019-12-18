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
typedef  int /*<<< orphan*/  u_char ;
struct evbuffer {size_t off; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/ * memchr (int /*<<< orphan*/ *,int /*<<< orphan*/  const,size_t) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

u_char *
evbuffer_find(struct evbuffer *buffer, const u_char *what, size_t len)
{
	size_t remain = buffer->off;
	u_char *search = buffer->buffer;
	u_char *p;

	while ((p = memchr(search, *what, remain)) != NULL) {
		remain = buffer->off - (size_t)(search - buffer->buffer);
		if (remain < len)
			break;
		if (memcmp(p, what, len) == 0)
			return (p);
		search = p + 1;
	}

	return (NULL);
}