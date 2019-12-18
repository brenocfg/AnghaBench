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
typedef  int /*<<< orphan*/  uint8_t ;
struct val_neg_zone {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dname_is_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  log_assert (int) ; 

__attribute__((used)) static size_t calc_zone_need(uint8_t* d, size_t len)
{
	size_t res = sizeof(struct val_neg_zone) + len;
	while(!dname_is_root(d)) {
		log_assert(len > 1); /* not root label */
		dname_remove_label(&d, &len);
		res += sizeof(struct val_neg_zone) + len;
	}
	return res;
}