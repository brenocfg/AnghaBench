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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_flushcache (char*,scalar_t__,size_t) ; 
 scalar_t__ page_address (struct page*) ; 

void memcpy_page_flushcache(char *to, struct page *page, size_t offset,
			    size_t len)
{
	memcpy_flushcache(to, page_address(page) + offset, len);
}