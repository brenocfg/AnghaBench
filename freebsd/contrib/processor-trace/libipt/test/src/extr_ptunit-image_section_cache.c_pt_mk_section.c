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
typedef  int uint8_t ;
typedef  void* uint64_t ;
struct pt_section {char const* filename; int ucount; int* content; int /*<<< orphan*/  lock; int /*<<< orphan*/  alock; void* size; void* offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pt_section*) ; 
 struct pt_section* malloc (int) ; 
 int /*<<< orphan*/  memset (struct pt_section*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_plain ; 
 int pte_bad_lock ; 
 int pte_nomem ; 
 int thrd_success ; 

int pt_mk_section(struct pt_section **psection, const char *filename,
		  uint64_t offset, uint64_t size)
{
	struct pt_section *section;
	uint8_t idx;

	section = malloc(sizeof(*section));
	if (!section)
		return -pte_nomem;

	memset(section, 0, sizeof(*section));
	section->filename = filename;
	section->offset = offset;
	section->size = size;
	section->ucount = 1;

	for (idx = 0; idx < sizeof(section->content); ++idx)
		section->content[idx] = idx;

#if defined(FEATURE_THREADS)
	{
		int errcode;

		errcode = mtx_init(&section->lock, mtx_plain);
		if (errcode != thrd_success) {
			free(section);
			return -pte_bad_lock;
		}

		errcode = mtx_init(&section->alock, mtx_plain);
		if (errcode != thrd_success) {
			mtx_destroy(&section->lock);
			free(section);
			return -pte_bad_lock;
		}
	}
#endif /* defined(FEATURE_THREADS) */

	*psection = section;

	return 0;
}