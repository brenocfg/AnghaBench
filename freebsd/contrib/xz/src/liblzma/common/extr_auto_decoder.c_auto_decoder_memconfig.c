#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ lzma_ret ;
struct TYPE_3__ {scalar_t__ (* memconfig ) (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__) ;int /*<<< orphan*/  coder; } ;
struct TYPE_4__ {scalar_t__ memlimit; TYPE_1__ next; } ;
typedef  TYPE_2__ lzma_auto_coder ;

/* Variables and functions */
 scalar_t__ LZMA_MEMLIMIT_ERROR ; 
 scalar_t__ LZMA_MEMUSAGE_BASE ; 
 scalar_t__ LZMA_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static lzma_ret
auto_decoder_memconfig(void *coder_ptr, uint64_t *memusage,
		uint64_t *old_memlimit, uint64_t new_memlimit)
{
	lzma_auto_coder *coder = coder_ptr;

	lzma_ret ret;

	if (coder->next.memconfig != NULL) {
		ret = coder->next.memconfig(coder->next.coder,
				memusage, old_memlimit, new_memlimit);
		assert(*old_memlimit == coder->memlimit);
	} else {
		// No coder is configured yet. Use the base value as
		// the current memory usage.
		*memusage = LZMA_MEMUSAGE_BASE;
		*old_memlimit = coder->memlimit;

		ret = LZMA_OK;
		if (new_memlimit != 0 && new_memlimit < *memusage)
			ret = LZMA_MEMLIMIT_ERROR;
	}

	if (ret == LZMA_OK && new_memlimit != 0)
		coder->memlimit = new_memlimit;

	return ret;
}