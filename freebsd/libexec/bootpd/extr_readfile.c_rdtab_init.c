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

/* Variables and functions */
 int /*<<< orphan*/  HASHTABLESIZE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  exit (int) ; 
 void* hash_Init (int /*<<< orphan*/ ) ; 
 void* hwhashtable ; 
 void* iphashtable ; 
 void* nmhashtable ; 
 int /*<<< orphan*/  report (int /*<<< orphan*/ ,char*) ; 

void
rdtab_init()
{
	hwhashtable = hash_Init(HASHTABLESIZE);
	iphashtable = hash_Init(HASHTABLESIZE);
	nmhashtable = hash_Init(HASHTABLESIZE);
	if (!(hwhashtable && iphashtable && nmhashtable)) {
		report(LOG_ERR, "Unable to allocate hash tables.");
		exit(1);
	}
}