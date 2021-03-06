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
struct umtxq_queue {int length; } ;
struct umtx_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMTXQ_LOCKED_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UMTX_SHARED_QUEUE ; 
 int /*<<< orphan*/  umtxq_getchain (struct umtx_key*) ; 
 struct umtxq_queue* umtxq_queue_lookup (struct umtx_key*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
umtxq_count(struct umtx_key *key)
{
	struct umtxq_queue *uh;

	UMTXQ_LOCKED_ASSERT(umtxq_getchain(key));
	uh = umtxq_queue_lookup(key, UMTX_SHARED_QUEUE);
	if (uh != NULL)
		return (uh->length);
	return (0);
}