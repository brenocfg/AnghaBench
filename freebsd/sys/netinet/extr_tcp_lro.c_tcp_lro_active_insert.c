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
struct lro_head {int dummy; } ;
struct lro_entry {int dummy; } ;
struct lro_ctrl {struct lro_head lro_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct lro_head*,struct lro_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_next ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static __inline void
tcp_lro_active_insert(struct lro_ctrl *lc, struct lro_head *bucket,
    struct lro_entry *le)
{

	LIST_INSERT_HEAD(&lc->lro_active, le, next);
	LIST_INSERT_HEAD(bucket, le, hash_next);
}