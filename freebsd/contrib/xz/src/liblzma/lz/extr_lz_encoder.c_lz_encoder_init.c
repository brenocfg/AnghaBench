#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int size; int write_pos; int hash_count; int sons_count; int /*<<< orphan*/  action; int /*<<< orphan*/  (* skip ) (TYPE_1__*,int) ;int /*<<< orphan*/ * buffer; scalar_t__ cyclic_pos; int /*<<< orphan*/ * hash; int /*<<< orphan*/ * son; scalar_t__ pending; scalar_t__ read_limit; scalar_t__ read_ahead; scalar_t__ read_pos; int /*<<< orphan*/  cyclic_size; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ lzma_mf ;
struct TYPE_7__ {scalar_t__ preset_dict_size; int /*<<< orphan*/ * preset_dict; } ;
typedef  TYPE_2__ lzma_lz_options ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int LZMA_MEMCMPLEN_EXTRA ; 
 int /*<<< orphan*/  LZMA_RUN ; 
 int /*<<< orphan*/  LZMA_SYNC_FLUSH ; 
 int SIZE_MAX ; 
 void* lzma_alloc (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * lzma_alloc_zero (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_free (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memzero (int /*<<< orphan*/ *,int) ; 
 int my_min (scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static bool
lz_encoder_init(lzma_mf *mf, const lzma_allocator *allocator,
		const lzma_lz_options *lz_options)
{
	// Allocate the history buffer.
	if (mf->buffer == NULL) {
		// lzma_memcmplen() is used for the dictionary buffer
		// so we need to allocate a few extra bytes to prevent
		// it from reading past the end of the buffer.
		mf->buffer = lzma_alloc(mf->size + LZMA_MEMCMPLEN_EXTRA,
				allocator);
		if (mf->buffer == NULL)
			return true;

		// Keep Valgrind happy with lzma_memcmplen() and initialize
		// the extra bytes whose value may get read but which will
		// effectively get ignored.
		memzero(mf->buffer + mf->size, LZMA_MEMCMPLEN_EXTRA);
	}

	// Use cyclic_size as initial mf->offset. This allows
	// avoiding a few branches in the match finders. The downside is
	// that match finder needs to be normalized more often, which may
	// hurt performance with huge dictionaries.
	mf->offset = mf->cyclic_size;
	mf->read_pos = 0;
	mf->read_ahead = 0;
	mf->read_limit = 0;
	mf->write_pos = 0;
	mf->pending = 0;

#if UINT32_MAX >= SIZE_MAX / 4
	// Check for integer overflow. (Huge dictionaries are not
	// possible on 32-bit CPU.)
	if (mf->hash_count > SIZE_MAX / sizeof(uint32_t)
			|| mf->sons_count > SIZE_MAX / sizeof(uint32_t))
		return true;
#endif

	// Allocate and initialize the hash table. Since EMPTY_HASH_VALUE
	// is zero, we can use lzma_alloc_zero() or memzero() for mf->hash.
	//
	// We don't need to initialize mf->son, but not doing that may
	// make Valgrind complain in normalization (see normalize() in
	// lz_encoder_mf.c). Skipping the initialization is *very* good
	// when big dictionary is used but only small amount of data gets
	// actually compressed: most of the mf->son won't get actually
	// allocated by the kernel, so we avoid wasting RAM and improve
	// initialization speed a lot.
	if (mf->hash == NULL) {
		mf->hash = lzma_alloc_zero(mf->hash_count * sizeof(uint32_t),
				allocator);
		mf->son = lzma_alloc(mf->sons_count * sizeof(uint32_t),
				allocator);

		if (mf->hash == NULL || mf->son == NULL) {
			lzma_free(mf->hash, allocator);
			mf->hash = NULL;

			lzma_free(mf->son, allocator);
			mf->son = NULL;

			return true;
		}
	} else {
/*
		for (uint32_t i = 0; i < mf->hash_count; ++i)
			mf->hash[i] = EMPTY_HASH_VALUE;
*/
		memzero(mf->hash, mf->hash_count * sizeof(uint32_t));
	}

	mf->cyclic_pos = 0;

	// Handle preset dictionary.
	if (lz_options->preset_dict != NULL
			&& lz_options->preset_dict_size > 0) {
		// If the preset dictionary is bigger than the actual
		// dictionary, use only the tail.
		mf->write_pos = my_min(lz_options->preset_dict_size, mf->size);
		memcpy(mf->buffer, lz_options->preset_dict
				+ lz_options->preset_dict_size - mf->write_pos,
				mf->write_pos);
		mf->action = LZMA_SYNC_FLUSH;
		mf->skip(mf, mf->write_pos);
	}

	mf->action = LZMA_RUN;

	return false;
}