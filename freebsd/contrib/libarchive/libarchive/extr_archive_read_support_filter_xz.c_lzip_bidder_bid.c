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
struct archive_read_filter_bidder {int dummy; } ;
struct archive_read_filter {int dummy; } ;

/* Variables and functions */
 int lzip_has_member (struct archive_read_filter*) ; 

__attribute__((used)) static int
lzip_bidder_bid(struct archive_read_filter_bidder *self,
    struct archive_read_filter *filter)
{

	(void)self; /* UNUSED */
	return (lzip_has_member(filter));
}