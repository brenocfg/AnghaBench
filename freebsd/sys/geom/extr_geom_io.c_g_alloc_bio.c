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
struct stack {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int,char*,struct bio*) ; 
 int /*<<< orphan*/  CTRSTACK (int,struct stack*,int) ; 
 int KTR_COMPILE ; 
 int KTR_GEOM ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  biozone ; 
 int ktr_mask ; 
 int /*<<< orphan*/  stack_save (struct stack*) ; 
 struct bio* uma_zalloc (int /*<<< orphan*/ ,int) ; 

struct bio *
g_alloc_bio(void)
{
	struct bio *bp;

	bp = uma_zalloc(biozone, M_WAITOK | M_ZERO);
#ifdef KTR
	if ((KTR_COMPILE & KTR_GEOM) && (ktr_mask & KTR_GEOM)) {
		struct stack st;

		CTR1(KTR_GEOM, "g_alloc_bio(): %p", bp);
		stack_save(&st);
		CTRSTACK(KTR_GEOM, &st, 3);
	}
#endif
	return (bp);
}