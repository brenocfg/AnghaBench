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
struct archive_read {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_RETRY ; 
 int do_uncompress_file (struct archive_read*) ; 

__attribute__((used)) static int uncompress_file(struct archive_read* a) {
	int ret;

	while(1) {
		/* Sometimes the uncompression function will return a
		 * 'retry' signal. If this will happen, we have to retry
		 * the function. */
		ret = do_uncompress_file(a);
		if(ret != ARCHIVE_RETRY)
			return ret;
	}
}