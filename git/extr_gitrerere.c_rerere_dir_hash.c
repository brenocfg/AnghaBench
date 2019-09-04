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
struct rerere_dir {unsigned char const* hash; } ;

/* Variables and functions */

__attribute__((used)) static const unsigned char *rerere_dir_hash(size_t i, void *table)
{
	struct rerere_dir **rr_dir = table;
	return rr_dir[i]->hash;
}