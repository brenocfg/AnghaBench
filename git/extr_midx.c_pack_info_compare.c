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
struct pack_info {int /*<<< orphan*/  pack_name; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pack_info_compare(const void *_a, const void *_b)
{
	struct pack_info *a = (struct pack_info *)_a;
	struct pack_info *b = (struct pack_info *)_b;
	return strcmp(a->pack_name, b->pack_name);
}