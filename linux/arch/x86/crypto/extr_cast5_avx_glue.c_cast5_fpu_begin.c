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
struct skcipher_walk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST5_BLOCK_SIZE ; 
 int /*<<< orphan*/  CAST5_PARALLEL_BLOCKS ; 
 int glue_fpu_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct skcipher_walk*,int,unsigned int) ; 

__attribute__((used)) static inline bool cast5_fpu_begin(bool fpu_enabled, struct skcipher_walk *walk,
				   unsigned int nbytes)
{
	return glue_fpu_begin(CAST5_BLOCK_SIZE, CAST5_PARALLEL_BLOCKS,
			      walk, fpu_enabled, nbytes);
}