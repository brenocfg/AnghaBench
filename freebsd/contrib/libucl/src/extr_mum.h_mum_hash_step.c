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
typedef  int uint64_t ;

/* Variables and functions */
 int _mum (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mum_hash_step_prime ; 
 int /*<<< orphan*/  _mum_key_step_prime ; 

__attribute__((used)) static inline uint64_t
mum_hash_step (uint64_t h, uint64_t key)
{
  return _mum (h, _mum_hash_step_prime) ^ _mum (key, _mum_key_step_prime);
}