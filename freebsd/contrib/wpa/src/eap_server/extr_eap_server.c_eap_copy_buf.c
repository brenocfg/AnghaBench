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
 struct wpabuf* wpabuf_dup (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static int eap_copy_buf(struct wpabuf **dst, const struct wpabuf *src)
{
	if (src == NULL)
		return -1;

	wpabuf_free(*dst);
	*dst = wpabuf_dup(src);
	return *dst ? 0 : -1;
}