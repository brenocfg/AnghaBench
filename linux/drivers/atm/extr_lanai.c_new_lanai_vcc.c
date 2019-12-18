#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  backlog; } ;
struct lanai_vcc {int vci; TYPE_1__ tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct lanai_vcc* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct lanai_vcc *new_lanai_vcc(void)
{
	struct lanai_vcc *lvcc;
	lvcc =  kzalloc(sizeof(*lvcc), GFP_KERNEL);
	if (likely(lvcc != NULL)) {
		skb_queue_head_init(&lvcc->tx.backlog);
#ifdef DEBUG
		lvcc->vci = -1;
#endif
	}
	return lvcc;
}