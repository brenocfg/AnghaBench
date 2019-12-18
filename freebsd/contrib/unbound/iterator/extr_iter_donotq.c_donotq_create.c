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
struct iter_donotq {int /*<<< orphan*/  region; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  donotq_delete (struct iter_donotq*) ; 
 int /*<<< orphan*/  regional_create () ; 

struct iter_donotq* 
donotq_create(void)
{
	struct iter_donotq* dq = (struct iter_donotq*)calloc(1,
		sizeof(struct iter_donotq));
	if(!dq)
		return NULL;
	dq->region = regional_create();
	if(!dq->region) {
		donotq_delete(dq);
		return NULL;
	}
	return dq;
}