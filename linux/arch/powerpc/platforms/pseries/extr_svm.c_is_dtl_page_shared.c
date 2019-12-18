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
 long dtl_nr_pages ; 
 struct page** dtl_page_store ; 

__attribute__((used)) static bool is_dtl_page_shared(struct page *page)
{
	long i;

	for (i = 0; i < dtl_nr_pages; i++)
		if (dtl_page_store[i] == page)
			return true;

	return false;
}