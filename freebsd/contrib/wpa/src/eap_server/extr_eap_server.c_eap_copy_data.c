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
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int eap_copy_data(u8 **dst, size_t *dst_len,
			 const u8 *src, size_t src_len)
{
	if (src == NULL)
		return -1;

	os_free(*dst);
	*dst = os_malloc(src_len);
	if (*dst) {
		os_memcpy(*dst, src, src_len);
		*dst_len = src_len;
		return 0;
	} else {
		*dst_len = 0;
		return -1;
	}
}