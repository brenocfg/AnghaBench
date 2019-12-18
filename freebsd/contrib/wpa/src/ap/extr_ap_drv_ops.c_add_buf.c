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
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf const*) ; 
 scalar_t__ wpabuf_resize (struct wpabuf**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_buf(struct wpabuf **dst, const struct wpabuf *src)
{
	if (!src)
		return 0;
	if (wpabuf_resize(dst, wpabuf_len(src)) != 0)
		return -1;
	wpabuf_put_buf(*dst, src);
	return 0;
}