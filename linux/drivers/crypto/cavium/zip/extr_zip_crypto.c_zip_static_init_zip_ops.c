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
struct zip_operation {int speed; int ccode; int lzs_flag; int begin_file; int end_file; int csum; scalar_t__ compcode; scalar_t__ history_len; int /*<<< orphan*/  format; int /*<<< orphan*/  flush; } ;

/* Variables and functions */
 int /*<<< orphan*/  LZS_FORMAT ; 
 int /*<<< orphan*/  ZIP_FLUSH_FINISH ; 
 int /*<<< orphan*/  ZLIB_FORMAT ; 

__attribute__((used)) static void zip_static_init_zip_ops(struct zip_operation *zip_ops,
				    int lzs_flag)
{
	zip_ops->flush        = ZIP_FLUSH_FINISH;

	/* equivalent to level 6 of opensource zlib */
	zip_ops->speed          = 1;

	if (!lzs_flag) {
		zip_ops->ccode		= 0; /* Auto Huffman */
		zip_ops->lzs_flag	= 0;
		zip_ops->format		= ZLIB_FORMAT;
	} else {
		zip_ops->ccode		= 3; /* LZS Encoding */
		zip_ops->lzs_flag	= 1;
		zip_ops->format		= LZS_FORMAT;
	}
	zip_ops->begin_file   = 1;
	zip_ops->history_len  = 0;
	zip_ops->end_file     = 1;
	zip_ops->compcode     = 0;
	zip_ops->csum	      = 1; /* Adler checksum desired */
}