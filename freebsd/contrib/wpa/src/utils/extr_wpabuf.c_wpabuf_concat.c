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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 

struct wpabuf * wpabuf_concat(struct wpabuf *a, struct wpabuf *b)
{
	struct wpabuf *n = NULL;
	size_t len = 0;

	if (b == NULL)
		return a;

	if (a)
		len += wpabuf_len(a);
	len += wpabuf_len(b);

	n = wpabuf_alloc(len);
	if (n) {
		if (a)
			wpabuf_put_buf(n, a);
		wpabuf_put_buf(n, b);
	}

	wpabuf_free(a);
	wpabuf_free(b);

	return n;
}