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
struct mtx {int dummy; } ;
struct malloc_type {int dummy; } ;
struct buf_ring {int br_prod_size; int br_cons_size; int br_prod_mask; int br_cons_mask; scalar_t__ br_cons_tail; scalar_t__ br_prod_tail; scalar_t__ br_cons_head; scalar_t__ br_prod_head; struct mtx* br_lock; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int M_ZERO ; 
 struct buf_ring* malloc (int,struct malloc_type*,int) ; 
 int /*<<< orphan*/  powerof2 (int) ; 

struct buf_ring *
buf_ring_alloc(int count, struct malloc_type *type, int flags, struct mtx *lock)
{
	struct buf_ring *br;

	KASSERT(powerof2(count), ("buf ring must be size power of 2"));
	
	br = malloc(sizeof(struct buf_ring) + count*sizeof(caddr_t),
	    type, flags|M_ZERO);
	if (br == NULL)
		return (NULL);
#ifdef DEBUG_BUFRING
	br->br_lock = lock;
#endif	
	br->br_prod_size = br->br_cons_size = count;
	br->br_prod_mask = br->br_cons_mask = count-1;
	br->br_prod_head = br->br_cons_head = 0;
	br->br_prod_tail = br->br_cons_tail = 0;
		
	return (br);
}