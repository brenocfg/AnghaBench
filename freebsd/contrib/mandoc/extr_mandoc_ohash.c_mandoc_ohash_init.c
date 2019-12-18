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
struct ohash_info {int /*<<< orphan*/  key_offset; int /*<<< orphan*/ * data; int /*<<< orphan*/  free; int /*<<< orphan*/  calloc; int /*<<< orphan*/  alloc; } ;
struct ohash {int dummy; } ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  hash_alloc ; 
 int /*<<< orphan*/  hash_calloc ; 
 int /*<<< orphan*/  hash_free ; 
 int /*<<< orphan*/  ohash_init (struct ohash*,unsigned int,struct ohash_info*) ; 

void
mandoc_ohash_init(struct ohash *h, unsigned int sz, ptrdiff_t ko)
{
	struct ohash_info info;

	info.alloc = hash_alloc;
	info.calloc = hash_calloc;
	info.free = hash_free;
	info.data = NULL;
	info.key_offset = ko;

	ohash_init(h, sz, &info);
}