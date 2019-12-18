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
struct TYPE_4__ {scalar_t__ bytes_remaining; } ;
struct TYPE_3__ {scalar_t__ solid; } ;
struct rar5 {TYPE_2__ file; int /*<<< orphan*/  skip_mode; TYPE_1__ main; } ;
struct archive_read {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_FATAL ; 
 scalar_t__ ARCHIVE_OK ; 
 scalar_t__ consume (struct archive_read*,scalar_t__) ; 
 struct rar5* get_context (struct archive_read*) ; 
 int rar5_read_data (struct archive_read*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rar5_read_data_skip(struct archive_read *a) {
	struct rar5* rar = get_context(a);

	if(rar->main.solid) {
		/* In solid archives, instead of skipping the data, we need to
		 * extract it, and dispose the result. The side effect of this
		 * operation will be setting up the initial window buffer state
		 * needed to be able to extract the selected file. */

		int ret;

		/* Make sure to process all blocks in the compressed stream. */
		while(rar->file.bytes_remaining > 0) {
			/* Setting the "skip mode" will allow us to skip
			 * checksum checks during data skipping. Checking the
			 * checksum of skipped data isn't really necessary and
			 * it's only slowing things down.
			 *
			 * This is incremented instead of setting to 1 because
			 * this data skipping function can be called
			 * recursively. */
			rar->skip_mode++;

			/* We're disposing 1 block of data, so we use triple
			 * NULLs in arguments. */
			ret = rar5_read_data(a, NULL, NULL, NULL);

			/* Turn off "skip mode". */
			rar->skip_mode--;

			if(ret < 0 || ret == ARCHIVE_EOF) {
				/* Propagate any potential error conditions
				 * to the caller. */
				return ret;
			}
		}
	} else {
		/* In standard archives, we can just jump over the compressed
		 * stream. Each file in non-solid archives starts from an empty
		 * window buffer. */

		if(ARCHIVE_OK != consume(a, rar->file.bytes_remaining)) {
			return ARCHIVE_FATAL;
		}

		rar->file.bytes_remaining = 0;
	}

	return ARCHIVE_OK;
}