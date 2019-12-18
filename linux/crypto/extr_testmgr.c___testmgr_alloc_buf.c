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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int XBUFSIZE ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 

__attribute__((used)) static int __testmgr_alloc_buf(char *buf[XBUFSIZE], int order)
{
	int i;

	for (i = 0; i < XBUFSIZE; i++) {
		buf[i] = (char *)__get_free_pages(GFP_KERNEL, order);
		if (!buf[i])
			goto err_free_buf;
	}

	return 0;

err_free_buf:
	while (i-- > 0)
		free_pages((unsigned long)buf[i], order);

	return -ENOMEM;
}