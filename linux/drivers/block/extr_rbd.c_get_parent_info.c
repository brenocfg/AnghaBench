#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rbd_device {TYPE_1__* spec; } ;
struct parent_image_info {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  snap_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int __get_parent_info (struct rbd_device*,struct page*,struct page*,struct parent_image_info*) ; 
 int __get_parent_info_legacy (struct rbd_device*,struct page*,struct page*,struct parent_image_info*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_encode_64 (void**,int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 

__attribute__((used)) static int get_parent_info(struct rbd_device *rbd_dev,
			   struct parent_image_info *pii)
{
	struct page *req_page, *reply_page;
	void *p;
	int ret;

	req_page = alloc_page(GFP_KERNEL);
	if (!req_page)
		return -ENOMEM;

	reply_page = alloc_page(GFP_KERNEL);
	if (!reply_page) {
		__free_page(req_page);
		return -ENOMEM;
	}

	p = page_address(req_page);
	ceph_encode_64(&p, rbd_dev->spec->snap_id);
	ret = __get_parent_info(rbd_dev, req_page, reply_page, pii);
	if (ret > 0)
		ret = __get_parent_info_legacy(rbd_dev, req_page, reply_page,
					       pii);

	__free_page(req_page);
	__free_page(reply_page);
	return ret;
}