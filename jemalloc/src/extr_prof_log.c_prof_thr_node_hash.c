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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  thr_uid; } ;
typedef  TYPE_1__ prof_thr_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  hash (int /*<<< orphan*/ *,int,int,size_t*) ; 

__attribute__((used)) static void
prof_thr_node_hash(const void *key, size_t r_hash[2]) {
	const prof_thr_node_t *thr_node = (prof_thr_node_t *)key;
	hash(&thr_node->thr_uid, sizeof(uint64_t), 0x94122f35U, r_hash);
}