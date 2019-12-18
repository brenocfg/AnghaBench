#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rbd_device {TYPE_2__* rbd_client; } ;
struct page {int dummy; } ;
struct ceph_osd_request {int /*<<< orphan*/  r_flags; int /*<<< orphan*/  r_base_oloc; int /*<<< orphan*/  r_base_oid; } ;
struct ceph_osd_client {int dummy; } ;
struct ceph_object_locator {int dummy; } ;
struct ceph_object_id {int dummy; } ;
struct TYPE_4__ {TYPE_1__* client; } ;
struct TYPE_3__ {struct ceph_osd_client osdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_FLAG_READ ; 
 int /*<<< orphan*/  CEPH_OSD_OP_READ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct page**) ; 
 int PTR_ERR (struct page**) ; 
 int calc_pages_for (int /*<<< orphan*/ ,int) ; 
 struct page** ceph_alloc_page_vector (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_copy_from_page_vector (struct page**,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ceph_oid_copy (int /*<<< orphan*/ *,struct ceph_object_id*) ; 
 int /*<<< orphan*/  ceph_oloc_copy (int /*<<< orphan*/ *,struct ceph_object_locator*) ; 
 int ceph_osdc_alloc_messages (struct ceph_osd_request*,int /*<<< orphan*/ ) ; 
 struct ceph_osd_request* ceph_osdc_alloc_request (struct ceph_osd_client*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_osdc_put_request (struct ceph_osd_request*) ; 
 int /*<<< orphan*/  ceph_osdc_start_request (struct ceph_osd_client*,struct ceph_osd_request*,int) ; 
 int ceph_osdc_wait_request (struct ceph_osd_client*,struct ceph_osd_request*) ; 
 int /*<<< orphan*/  osd_req_op_extent_init (struct ceph_osd_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_req_op_extent_osd_data_pages (struct ceph_osd_request*,int /*<<< orphan*/ ,struct page**,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int rbd_obj_read_sync(struct rbd_device *rbd_dev,
			     struct ceph_object_id *oid,
			     struct ceph_object_locator *oloc,
			     void *buf, int buf_len)

{
	struct ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	struct ceph_osd_request *req;
	struct page **pages;
	int num_pages = calc_pages_for(0, buf_len);
	int ret;

	req = ceph_osdc_alloc_request(osdc, NULL, 1, false, GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	ceph_oid_copy(&req->r_base_oid, oid);
	ceph_oloc_copy(&req->r_base_oloc, oloc);
	req->r_flags = CEPH_OSD_FLAG_READ;

	pages = ceph_alloc_page_vector(num_pages, GFP_KERNEL);
	if (IS_ERR(pages)) {
		ret = PTR_ERR(pages);
		goto out_req;
	}

	osd_req_op_extent_init(req, 0, CEPH_OSD_OP_READ, 0, buf_len, 0, 0);
	osd_req_op_extent_osd_data_pages(req, 0, pages, buf_len, 0, false,
					 true);

	ret = ceph_osdc_alloc_messages(req, GFP_KERNEL);
	if (ret)
		goto out_req;

	ceph_osdc_start_request(osdc, req, false);
	ret = ceph_osdc_wait_request(osdc, req);
	if (ret >= 0)
		ceph_copy_from_page_vector(pages, buf, 0, ret);

out_req:
	ceph_osdc_put_request(req);
	return ret;
}