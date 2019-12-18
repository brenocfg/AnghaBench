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
 scalar_t__ hexstr2bin (char const*,int /*<<< orphan*/ ,size_t) ; 
 size_t os_strlen (char const*) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf*,size_t) ; 

struct wpabuf * wpabuf_parse_bin(const char *buf)
{
	size_t len;
	struct wpabuf *ret;

	len = os_strlen(buf);
	if (len & 0x01)
		return NULL;
	len /= 2;

	ret = wpabuf_alloc(len);
	if (ret == NULL)
		return NULL;

	if (hexstr2bin(buf, wpabuf_put(ret, len), len)) {
		wpabuf_free(ret);
		return NULL;
	}

	return ret;
}