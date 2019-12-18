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
 int /*<<< orphan*/  _PAGE_CACHE_MODE_WT ; 
 int _set_pages_array (struct page**,int,int /*<<< orphan*/ ) ; 

int set_pages_array_wt(struct page **pages, int numpages)
{
	return _set_pages_array(pages, numpages, _PAGE_CACHE_MODE_WT);
}