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
struct tcp_function_block {int /*<<< orphan*/  tfb_refcnt; } ;

/* Variables and functions */
 struct tcp_function_block* find_tcp_fb_locked (struct tcp_function_block*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_runlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_function_lock ; 

struct tcp_function_block *
find_and_ref_tcp_fb(struct tcp_function_block *blk)
{
	struct tcp_function_block *rblk;
	
	rw_rlock(&tcp_function_lock);	
	rblk = find_tcp_fb_locked(blk, NULL);
	if (rblk) 
		refcount_acquire(&rblk->tfb_refcnt);
	rw_runlock(&tcp_function_lock);
	return(rblk);
}