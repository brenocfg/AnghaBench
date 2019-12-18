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
struct umtx_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  umtxq_lock (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_unbusy (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_unlock (struct umtx_key*) ; 

__attribute__((used)) static inline void
umtxq_unbusy_unlocked(struct umtx_key *key)
{

	umtxq_lock(key);
	umtxq_unbusy(key);
	umtxq_unlock(key);
}