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
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 

struct wpabuf * wpabuf_zeropad(struct wpabuf *buf, size_t len)
{
	struct wpabuf *ret;
	size_t blen;

	if (buf == NULL)
		return NULL;

	blen = wpabuf_len(buf);
	if (blen >= len)
		return buf;

	ret = wpabuf_alloc(len);
	if (ret) {
		os_memset(wpabuf_put(ret, len - blen), 0, len - blen);
		wpabuf_put_buf(ret, buf);
	}
	wpabuf_free(buf);

	return ret;
}