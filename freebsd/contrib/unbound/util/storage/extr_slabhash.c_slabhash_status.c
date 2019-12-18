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
struct slabhash {size_t size; int /*<<< orphan*/ * array; int /*<<< orphan*/  shift; scalar_t__ mask; } ;
typedef  int /*<<< orphan*/  num ;

/* Variables and functions */
 int /*<<< orphan*/  log_info (char*,char const*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lruhash_status (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

void slabhash_status(struct slabhash* sl, const char* id, int extended)
{
	size_t i;
	char num[17];
	log_info("Slabhash %s: %u tables mask=%x shift=%d", 
		id, (unsigned)sl->size, (unsigned)sl->mask, sl->shift);
	for(i=0; i<sl->size; i++) {
		snprintf(num, sizeof(num), "table %u", (unsigned)i);
		lruhash_status(sl->array[i], num, extended);
	}
}