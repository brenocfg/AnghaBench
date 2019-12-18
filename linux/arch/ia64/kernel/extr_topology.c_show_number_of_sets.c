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
struct TYPE_2__ {unsigned int pcci_cache_size; unsigned int pcci_assoc; int pcci_line_size; } ;
struct cache_info {TYPE_1__ cci; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static ssize_t show_number_of_sets(struct cache_info *this_leaf, char *buf)
{
	unsigned number_of_sets = this_leaf->cci.pcci_cache_size;
	number_of_sets /= this_leaf->cci.pcci_assoc;
	number_of_sets /= 1 << this_leaf->cci.pcci_line_size;

	return sprintf(buf, "%u\n", number_of_sets);
}