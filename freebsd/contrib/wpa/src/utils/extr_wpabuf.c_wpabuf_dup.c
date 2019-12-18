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
 struct wpabuf* wpabuf_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct wpabuf * wpabuf_dup(const struct wpabuf *src)
{
	struct wpabuf *buf = wpabuf_alloc(wpabuf_len(src));
	if (buf)
		wpabuf_put_data(buf, wpabuf_head(src), wpabuf_len(src));
	return buf;
}