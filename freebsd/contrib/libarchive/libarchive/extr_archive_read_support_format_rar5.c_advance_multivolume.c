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
struct TYPE_2__ {int endarc; } ;
struct rar5 {TYPE_1__ main; } ;
struct archive_read {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
#define  ARCHIVE_OK 129 
#define  ARCHIVE_RETRY 128 
 struct rar5* get_context (struct archive_read*) ; 
 int skip_base_block (struct archive_read*) ; 

__attribute__((used)) static int advance_multivolume(struct archive_read* a) {
	int lret;
	struct rar5* rar = get_context(a);

	/* A small state machine that will skip unnecessary data, needed to
	 * switch from one multivolume to another. Such skipping is needed if
	 * we want to be an stream-oriented (instead of file-oriented)
	 * unpacker.
	 *
	 * The state machine starts with `rar->main.endarc` == 0. It also
	 * assumes that current stream pointer points to some base block
	 * header.
	 *
	 * The `endarc` field is being set when the base block parsing
	 * function encounters the 'end of archive' marker.
	 */

	while(1) {
		if(rar->main.endarc == 1) {
			int looping = 1;

			rar->main.endarc = 0;

			while(looping) {
				lret = skip_base_block(a);
				switch(lret) {
					case ARCHIVE_RETRY:
						/* Continue looping. */
						break;
					case ARCHIVE_OK:
						/* Break loop. */
						looping = 0;
						break;
					default:
						/* Forward any errors to the
						 * caller. */
						return lret;
				}
			}

			break;
		} else {
			/* Skip current base block. In order to properly skip
			 * it, we really need to simply parse it and discard
			 * the results. */

			lret = skip_base_block(a);
			if(lret == ARCHIVE_FATAL || lret == ARCHIVE_FAILED)
				return lret;

			/* The `skip_base_block` function tells us if we
			 * should continue with skipping, or we should stop
			 * skipping. We're trying to skip everything up to
			 * a base FILE block. */

			if(lret != ARCHIVE_RETRY) {
				/* If there was an error during skipping, or we
				 * have just skipped a FILE base block... */

				if(rar->main.endarc == 0) {
					return lret;
				} else {
					continue;
				}
			}
		}
	}

	return ARCHIVE_OK;
}