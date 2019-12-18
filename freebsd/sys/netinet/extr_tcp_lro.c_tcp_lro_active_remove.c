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
struct lro_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct lro_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_next ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static __inline void
tcp_lro_active_remove(struct lro_entry *le)
{

	LIST_REMOVE(le, next);		/* active list */
	LIST_REMOVE(le, hash_next);	/* hash bucket */
}