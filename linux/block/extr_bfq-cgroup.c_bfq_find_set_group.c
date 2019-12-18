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
struct blkcg {int dummy; } ;
struct bfq_group {int dummy; } ;
struct bfq_data {struct bfq_group* root_group; } ;

/* Variables and functions */

struct bfq_group *bfq_find_set_group(struct bfq_data *bfqd, struct blkcg *blkcg)
{
	return bfqd->root_group;
}