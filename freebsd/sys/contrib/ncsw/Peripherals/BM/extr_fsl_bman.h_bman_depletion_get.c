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
typedef  int /*<<< orphan*/  uint8_t ;
struct bman_depletion {int* __state; } ;

/* Variables and functions */
 int __bmdep_bit (int /*<<< orphan*/ ) ; 
 size_t __bmdep_word (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ int bman_depletion_get(const struct bman_depletion *c, uint8_t bpid)
{
    return (int)(c->__state[__bmdep_word(bpid)] & __bmdep_bit(bpid));
}