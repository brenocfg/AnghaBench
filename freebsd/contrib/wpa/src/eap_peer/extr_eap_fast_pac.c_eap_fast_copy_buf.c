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

/* Variables and functions */
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int eap_fast_copy_buf(u8 **dst, size_t *dst_len,
			     const u8 *src, size_t src_len)
{
	if (src) {
		*dst = os_memdup(src, src_len);
		if (*dst == NULL)
			return -1;
		*dst_len = src_len;
	}
	return 0;
}