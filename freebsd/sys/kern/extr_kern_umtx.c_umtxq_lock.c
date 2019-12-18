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
struct umtxq_chain {int /*<<< orphan*/  uc_lock; } ;
struct umtx_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 struct umtxq_chain* umtxq_getchain (struct umtx_key*) ; 

__attribute__((used)) static inline void
umtxq_lock(struct umtx_key *key)
{
	struct umtxq_chain *uc;

	uc = umtxq_getchain(key);
	mtx_lock(&uc->uc_lock);
}