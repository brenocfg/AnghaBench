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
struct request_queue {int dummy; } ;
struct page {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int __bio_add_pc_page (struct request_queue*,struct bio*,struct page*,unsigned int,unsigned int,int*) ; 

int bio_add_pc_page(struct request_queue *q, struct bio *bio,
		struct page *page, unsigned int len, unsigned int offset)
{
	bool same_page = false;
	return __bio_add_pc_page(q, bio, page, len, offset, &same_page);
}