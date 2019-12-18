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

/* Variables and functions */
 int /*<<< orphan*/  DIAG304_QUERY_PRP ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 unsigned long hypfs_sprp_diag304 (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hypfs_sprp_create(void **data_ptr, void **free_ptr, size_t *size)
{
	unsigned long rc;
	void *data;

	data = (void *) get_zeroed_page(GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	rc = hypfs_sprp_diag304(data, DIAG304_QUERY_PRP);
	if (rc != 1) {
		*data_ptr = *free_ptr = NULL;
		*size = 0;
		free_page((unsigned long) data);
		return -EIO;
	}
	*data_ptr = *free_ptr = data;
	*size = PAGE_SIZE;
	return 0;
}