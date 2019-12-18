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
typedef  int /*<<< orphan*/  u32 ;
struct parent_image_info {int /*<<< orphan*/  snap_id; int /*<<< orphan*/ * image_id; int /*<<< orphan*/ * pool_ns; int /*<<< orphan*/  pool_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_decode_64_safe (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ceph_extract_encoded_string (void**,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ceph_start_decoding (void**,void*,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_inval ; 

__attribute__((used)) static int decode_parent_image_spec(void **p, void *end,
				    struct parent_image_info *pii)
{
	u8 struct_v;
	u32 struct_len;
	int ret;

	ret = ceph_start_decoding(p, end, 1, "ParentImageSpec",
				  &struct_v, &struct_len);
	if (ret)
		return ret;

	ceph_decode_64_safe(p, end, pii->pool_id, e_inval);
	pii->pool_ns = ceph_extract_encoded_string(p, end, NULL, GFP_KERNEL);
	if (IS_ERR(pii->pool_ns)) {
		ret = PTR_ERR(pii->pool_ns);
		pii->pool_ns = NULL;
		return ret;
	}
	pii->image_id = ceph_extract_encoded_string(p, end, NULL, GFP_KERNEL);
	if (IS_ERR(pii->image_id)) {
		ret = PTR_ERR(pii->image_id);
		pii->image_id = NULL;
		return ret;
	}
	ceph_decode_64_safe(p, end, pii->snap_id, e_inval);
	return 0;

e_inval:
	return -EINVAL;
}