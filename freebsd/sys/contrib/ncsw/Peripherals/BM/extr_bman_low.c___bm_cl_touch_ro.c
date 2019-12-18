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
struct bm_addr {int /*<<< orphan*/  addr_ce; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcbt_ro (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr_ADD (int /*<<< orphan*/ ,uintptr_t) ; 

__attribute__((used)) static __inline__ void __bm_cl_touch_ro(struct bm_addr *bm, uintptr_t offset)
{
    dcbt_ro(ptr_ADD(bm->addr_ce, offset));
}