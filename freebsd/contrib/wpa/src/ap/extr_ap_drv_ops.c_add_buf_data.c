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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ wpabuf_resize (struct wpabuf**,size_t) ; 

__attribute__((used)) static int add_buf_data(struct wpabuf **dst, const u8 *data, size_t len)
{
	if (!data || !len)
		return 0;
	if (wpabuf_resize(dst, len) != 0)
		return -1;
	wpabuf_put_data(*dst, data, len);
	return 0;
}