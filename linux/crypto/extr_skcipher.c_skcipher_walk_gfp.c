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
struct skcipher_walk {int flags; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SKCIPHER_WALK_SLEEP ; 

__attribute__((used)) static inline gfp_t skcipher_walk_gfp(struct skcipher_walk *walk)
{
	return walk->flags & SKCIPHER_WALK_SLEEP ? GFP_KERNEL : GFP_ATOMIC;
}