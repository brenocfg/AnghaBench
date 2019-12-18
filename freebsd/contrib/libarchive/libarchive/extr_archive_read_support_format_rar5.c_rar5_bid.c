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
struct archive_read {int dummy; } ;

/* Variables and functions */
 int bid_standard (struct archive_read*) ; 

__attribute__((used)) static int rar5_bid(struct archive_read* a, int best_bid) {
	int my_bid;

	if(best_bid > 30)
		return -1;

	my_bid = bid_standard(a);
	if(my_bid > -1) {
		return my_bid;
	}

	return -1;
}