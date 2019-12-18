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
struct regional {int dummy; } ;

/* Variables and functions */
 int ALIGNMENT ; 
 int REGIONAL_CHUNK_SIZE ; 
 int REGIONAL_LARGE_OBJECT_SIZE ; 
 scalar_t__ count_chunks (struct regional*) ; 
 scalar_t__ count_large (struct regional*) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_info (char*,unsigned int,unsigned int) ; 

void 
regional_log_stats(struct regional *r)
{
	/* some basic assertions put here (non time critical code) */
	log_assert(ALIGNMENT >= sizeof(char*));
	log_assert(REGIONAL_CHUNK_SIZE > ALIGNMENT);
	log_assert(REGIONAL_CHUNK_SIZE-ALIGNMENT > REGIONAL_LARGE_OBJECT_SIZE);
	log_assert(REGIONAL_CHUNK_SIZE >= sizeof(struct regional));
	/* debug print */
	log_info("regional %u chunks, %u large",
		(unsigned)count_chunks(r), (unsigned)count_large(r));
}