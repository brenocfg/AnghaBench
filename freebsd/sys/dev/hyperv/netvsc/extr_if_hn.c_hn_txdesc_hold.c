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
struct hn_txdesc {scalar_t__ refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  atomic_add_int (scalar_t__*,int) ; 

__attribute__((used)) static __inline void
hn_txdesc_hold(struct hn_txdesc *txd)
{

	/* 0->1 transition will never work */
	KASSERT(txd->refs > 0, ("invalid txd refs %d", txd->refs));
	atomic_add_int(&txd->refs, 1);
}