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
typedef  int /*<<< orphan*/  uint32_t ;
struct relocs {int count; int size; int /*<<< orphan*/ * offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,unsigned long) ; 
 void* realloc (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void add_reloc(struct relocs *r, uint32_t offset)
{
	if (r->count == r->size) {
		unsigned long newsize = r->size + 50000;
		void *mem = realloc(r->offset, newsize * sizeof(r->offset[0]));

		if (!mem)
			die("realloc of %ld entries for relocs failed\n",
                                newsize);
		r->offset = mem;
		r->size = newsize;
	}
	r->offset[r->count++] = offset;
}