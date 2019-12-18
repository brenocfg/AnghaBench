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
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bio_add_page (struct bio*,struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  __bio_try_merge_page (struct bio*,struct page*,unsigned int,unsigned int,int*) ; 
 scalar_t__ bio_full (struct bio*,unsigned int) ; 

int bio_add_page(struct bio *bio, struct page *page,
		 unsigned int len, unsigned int offset)
{
	bool same_page = false;

	if (!__bio_try_merge_page(bio, page, len, offset, &same_page)) {
		if (bio_full(bio, len))
			return 0;
		__bio_add_page(bio, page, len, offset);
	}
	return len;
}