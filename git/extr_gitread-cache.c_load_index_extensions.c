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
typedef  scalar_t__ uint32_t ;
struct load_index_extensions {unsigned long src_offset; int mmap_size; scalar_t__ mmap; int /*<<< orphan*/  istate; } ;
struct TYPE_2__ {int rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 scalar_t__ get_be32 (scalar_t__) ; 
 int /*<<< orphan*/  munmap (void*,int) ; 
 scalar_t__ read_index_extension (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static void *load_index_extensions(void *_data)
{
	struct load_index_extensions *p = _data;
	unsigned long src_offset = p->src_offset;

	while (src_offset <= p->mmap_size - the_hash_algo->rawsz - 8) {
		/* After an array of active_nr index entries,
		 * there can be arbitrary number of extended
		 * sections, each of which is prefixed with
		 * extension name (4-byte) and section length
		 * in 4-byte network byte order.
		 */
		uint32_t extsize = get_be32(p->mmap + src_offset + 4);
		if (read_index_extension(p->istate,
					 p->mmap + src_offset,
					 p->mmap + src_offset + 8,
					 extsize) < 0) {
			munmap((void *)p->mmap, p->mmap_size);
			die(_("index file corrupt"));
		}
		src_offset += 8;
		src_offset += extsize;
	}

	return NULL;
}