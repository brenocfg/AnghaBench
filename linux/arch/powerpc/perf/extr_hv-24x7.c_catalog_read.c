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
typedef  scalar_t__ uint64_t ;
struct kobject {int dummy; } ;
struct hv_24x7_catalog_page_0 {int /*<<< orphan*/  length; int /*<<< orphan*/  version; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int loff_t ;

/* Variables and functions */
 size_t EIO ; 
 size_t ENOMEM ; 
 int /*<<< orphan*/  GFP_USER ; 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 long h_get_24x7_catalog_page (void*,scalar_t__,int) ; 
 int /*<<< orphan*/  hv_page_cache ; 
 void* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memcpy (char*,void*,size_t) ; 
 int /*<<< orphan*/  pr_devel (char*,int,int,size_t,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,int,long) ; 

__attribute__((used)) static ssize_t catalog_read(struct file *filp, struct kobject *kobj,
			    struct bin_attribute *bin_attr, char *buf,
			    loff_t offset, size_t count)
{
	long hret;
	ssize_t ret = 0;
	size_t catalog_len = 0, catalog_page_len = 0;
	loff_t page_offset = 0;
	loff_t offset_in_page;
	size_t copy_len;
	uint64_t catalog_version_num = 0;
	void *page = kmem_cache_alloc(hv_page_cache, GFP_USER);
	struct hv_24x7_catalog_page_0 *page_0 = page;

	if (!page)
		return -ENOMEM;

	hret = h_get_24x7_catalog_page(page, 0, 0);
	if (hret) {
		ret = -EIO;
		goto e_free;
	}

	catalog_version_num = be64_to_cpu(page_0->version);
	catalog_page_len = be32_to_cpu(page_0->length);
	catalog_len = catalog_page_len * 4096;

	page_offset = offset / 4096;
	offset_in_page = offset % 4096;

	if (page_offset >= catalog_page_len)
		goto e_free;

	if (page_offset != 0) {
		hret = h_get_24x7_catalog_page(page, catalog_version_num,
					       page_offset);
		if (hret) {
			ret = -EIO;
			goto e_free;
		}
	}

	copy_len = 4096 - offset_in_page;
	if (copy_len > count)
		copy_len = count;

	memcpy(buf, page+offset_in_page, copy_len);
	ret = copy_len;

e_free:
	if (hret)
		pr_err("h_get_24x7_catalog_page(ver=%lld, page=%lld) failed:"
		       " rc=%ld\n",
		       catalog_version_num, page_offset, hret);
	kmem_cache_free(hv_page_cache, page);

	pr_devel("catalog_read: offset=%lld(%lld) count=%zu "
			"catalog_len=%zu(%zu) => %zd\n", offset, page_offset,
			count, catalog_len, catalog_page_len, ret);

	return ret;
}