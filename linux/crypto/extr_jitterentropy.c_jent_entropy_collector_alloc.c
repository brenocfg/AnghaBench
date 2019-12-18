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
struct rand_data {unsigned int osr; int /*<<< orphan*/  memaccessloops; int /*<<< orphan*/  memblocks; int /*<<< orphan*/  memblocksize; void* mem; } ;

/* Variables and functions */
 unsigned int JENT_DISABLE_MEMORY_ACCESS ; 
 int /*<<< orphan*/  JENT_MEMORY_ACCESSLOOPS ; 
 int /*<<< orphan*/  JENT_MEMORY_BLOCKS ; 
 int /*<<< orphan*/  JENT_MEMORY_BLOCKSIZE ; 
 int JENT_MEMORY_SIZE ; 
 int /*<<< orphan*/  jent_gen_entropy (struct rand_data*) ; 
 void* jent_zalloc (int) ; 
 int /*<<< orphan*/  jent_zfree (struct rand_data*) ; 

struct rand_data *jent_entropy_collector_alloc(unsigned int osr,
					       unsigned int flags)
{
	struct rand_data *entropy_collector;

	entropy_collector = jent_zalloc(sizeof(struct rand_data));
	if (!entropy_collector)
		return NULL;

	if (!(flags & JENT_DISABLE_MEMORY_ACCESS)) {
		/* Allocate memory for adding variations based on memory
		 * access
		 */
		entropy_collector->mem = jent_zalloc(JENT_MEMORY_SIZE);
		if (!entropy_collector->mem) {
			jent_zfree(entropy_collector);
			return NULL;
		}
		entropy_collector->memblocksize = JENT_MEMORY_BLOCKSIZE;
		entropy_collector->memblocks = JENT_MEMORY_BLOCKS;
		entropy_collector->memaccessloops = JENT_MEMORY_ACCESSLOOPS;
	}

	/* verify and set the oversampling rate */
	if (0 == osr)
		osr = 1; /* minimum sampling rate is 1 */
	entropy_collector->osr = osr;

	/* fill the data pad with non-zero values */
	jent_gen_entropy(entropy_collector);

	return entropy_collector;
}