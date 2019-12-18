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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_64_safe (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ceph_start_decoding (void**,void*,int,char*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  e_inval ; 

__attribute__((used)) static int decode_object_map_header(void **p, void *end, u64 *object_map_size)
{
	u8 struct_v;
	u32 struct_len;
	u32 header_len;
	void *header_end;
	int ret;

	ceph_decode_32_safe(p, end, header_len, e_inval);
	header_end = *p + header_len;

	ret = ceph_start_decoding(p, end, 1, "BitVector header", &struct_v,
				  &struct_len);
	if (ret)
		return ret;

	ceph_decode_64_safe(p, end, *object_map_size, e_inval);

	*p = header_end;
	return 0;

e_inval:
	return -EINVAL;
}