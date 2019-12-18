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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 size_t mum_hash_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mum_hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mum_hash_step (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline size_t
mum_hash64 (uint64_t key, uint64_t seed) {
  return mum_hash_finish (mum_hash_step (mum_hash_init (seed), key));
}