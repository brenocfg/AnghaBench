#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ memusage_max; scalar_t__ min_version; int /*<<< orphan*/  all_have_sizes; int /*<<< orphan*/  idx; scalar_t__ stream_padding; } ;
typedef  TYPE_1__ xz_file_info ;
struct TYPE_5__ {scalar_t__ memusage_max; scalar_t__ min_version; int /*<<< orphan*/  all_have_sizes; int /*<<< orphan*/  checks; int /*<<< orphan*/  stream_padding; int /*<<< orphan*/  uncompressed_size; int /*<<< orphan*/  compressed_size; int /*<<< orphan*/  blocks; int /*<<< orphan*/  streams; int /*<<< orphan*/  files; } ;

/* Variables and functions */
 scalar_t__ lzma_index_block_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_index_checks (int /*<<< orphan*/ ) ; 
 scalar_t__ lzma_index_file_size (int /*<<< orphan*/ ) ; 
 scalar_t__ lzma_index_stream_count (int /*<<< orphan*/ ) ; 
 scalar_t__ lzma_index_uncompressed_size (int /*<<< orphan*/ ) ; 
 TYPE_3__ totals ; 

__attribute__((used)) static void
update_totals(const xz_file_info *xfi)
{
	// TODO: Integer overflow checks
	++totals.files;
	totals.streams += lzma_index_stream_count(xfi->idx);
	totals.blocks += lzma_index_block_count(xfi->idx);
	totals.compressed_size += lzma_index_file_size(xfi->idx);
	totals.uncompressed_size += lzma_index_uncompressed_size(xfi->idx);
	totals.stream_padding += xfi->stream_padding;
	totals.checks |= lzma_index_checks(xfi->idx);

	if (totals.memusage_max < xfi->memusage_max)
		totals.memusage_max = xfi->memusage_max;

	if (totals.min_version < xfi->min_version)
		totals.min_version = xfi->min_version;

	totals.all_have_sizes &= xfi->all_have_sizes;

	return;
}