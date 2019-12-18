#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  idx; } ;
typedef  TYPE_1__ xz_file_info ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 TYPE_1__ XZ_FILE_INFO_INIT ; 
 int /*<<< orphan*/  lzma_index_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_index_uncompressed_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_indexes (TYPE_1__*,int) ; 

off_t
unxz_len(int fd)
{
	xz_file_info xfi = XZ_FILE_INFO_INIT;
	if (!parse_indexes(&xfi, fd)) {
		off_t res = lzma_index_uncompressed_size(xfi.idx);
		lzma_index_end(xfi.idx, NULL);
		return res;
	}
	return 0;
}