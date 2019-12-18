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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int write_ptr; int last_block_start; int last_block_length; } ;
struct rar5 {TYPE_1__ cstate; } ;
struct filter_info {int type; int block_start; int block_length; int channels; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FATAL ; 
 scalar_t__ ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FILTER_ARM ; 
 int FILTER_DELTA ; 
 struct filter_info* add_new_filter (struct rar5*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct rar5* get_context (struct archive_read*) ; 
 int /*<<< orphan*/  is_valid_filter_block_start (struct rar5*,int) ; 
 scalar_t__ parse_filter_data (struct rar5*,int /*<<< orphan*/  const*,int*) ; 
 scalar_t__ read_bits_16 (struct rar5*,int /*<<< orphan*/  const*,int*) ; 
 scalar_t__ read_consume_bits (struct rar5*,int /*<<< orphan*/  const*,int,int*) ; 
 int /*<<< orphan*/  skip_bits (struct rar5*,int) ; 

__attribute__((used)) static int parse_filter(struct archive_read* ar, const uint8_t* p) {
	uint32_t block_start, block_length;
	uint16_t filter_type;
	struct rar5* rar = get_context(ar);

	/* Read the parameters from the input stream. */
	if(ARCHIVE_OK != parse_filter_data(rar, p, &block_start))
		return ARCHIVE_EOF;

	if(ARCHIVE_OK != parse_filter_data(rar, p, &block_length))
		return ARCHIVE_EOF;

	if(ARCHIVE_OK != read_bits_16(rar, p, &filter_type))
		return ARCHIVE_EOF;

	filter_type >>= 13;
	skip_bits(rar, 3);

	/* Perform some sanity checks on this filter parameters. Note that we
	 * allow only DELTA, E8/E9 and ARM filters here, because rest of
	 * filters are not used in RARv5. */

	if(block_length < 4 ||
	    block_length > 0x400000 ||
	    filter_type > FILTER_ARM ||
	    !is_valid_filter_block_start(rar, block_start))
	{
		archive_set_error(&ar->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Invalid filter encountered");
		return ARCHIVE_FATAL;
	}

	/* Allocate a new filter. */
	struct filter_info* filt = add_new_filter(rar);
	if(filt == NULL) {
		archive_set_error(&ar->archive, ENOMEM,
		    "Can't allocate memory for a filter descriptor.");
		return ARCHIVE_FATAL;
	}

	filt->type = filter_type;
	filt->block_start = rar->cstate.write_ptr + block_start;
	filt->block_length = block_length;

	rar->cstate.last_block_start = filt->block_start;
	rar->cstate.last_block_length = filt->block_length;

	/* Read some more data in case this is a DELTA filter. Other filter
	 * types don't require any additional data over what was already
	 * read. */
	if(filter_type == FILTER_DELTA) {
		int channels;

		if(ARCHIVE_OK != read_consume_bits(rar, p, 5, &channels))
			return ARCHIVE_EOF;

		filt->channels = channels + 1;
	}

	return ARCHIVE_OK;
}