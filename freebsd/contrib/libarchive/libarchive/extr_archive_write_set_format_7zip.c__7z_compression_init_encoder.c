#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct archive_write {int /*<<< orphan*/  archive; scalar_t__ format_data; } ;
struct TYPE_7__ {int avail_out; scalar_t__ total_out; int /*<<< orphan*/  next_out; scalar_t__ total_in; } ;
struct _7zip {TYPE_1__ stream; int /*<<< orphan*/  wbuff; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  PPMD7_DEFAULT_MEM_SIZE ; 
 int /*<<< orphan*/  PPMD7_DEFAULT_ORDER ; 
#define  _7Z_BZIP2 133 
#define  _7Z_COPY 132 
#define  _7Z_DEFLATE 131 
#define  _7Z_LZMA1 130 
#define  _7Z_LZMA2 129 
#define  _7Z_PPMD 128 
 int compression_init_encoder_bzip2 (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int compression_init_encoder_copy (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int compression_init_encoder_deflate (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int compression_init_encoder_lzma1 (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int compression_init_encoder_lzma2 (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int compression_init_encoder_ppmd (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_7z_compression_init_encoder(struct archive_write *a, unsigned compression,
    int compression_level)
{
	struct _7zip *zip;
	int r;

	zip = (struct _7zip *)a->format_data;
	switch (compression) {
	case _7Z_DEFLATE:
		r = compression_init_encoder_deflate(
		    &(a->archive), &(zip->stream),
		    compression_level, 0);
		break;
	case _7Z_BZIP2:
		r = compression_init_encoder_bzip2(
		    &(a->archive), &(zip->stream),
		    compression_level);
		break;
	case _7Z_LZMA1:
		r = compression_init_encoder_lzma1(
		    &(a->archive), &(zip->stream),
		    compression_level);
		break;
	case _7Z_LZMA2:
		r = compression_init_encoder_lzma2(
		    &(a->archive), &(zip->stream),
		    compression_level);
		break;
	case _7Z_PPMD:
		r = compression_init_encoder_ppmd(
		    &(a->archive), &(zip->stream),
		    PPMD7_DEFAULT_ORDER, PPMD7_DEFAULT_MEM_SIZE);
		break;
	case _7Z_COPY:
	default:
		r = compression_init_encoder_copy(
		    &(a->archive), &(zip->stream));
		break;
	}
	if (r == ARCHIVE_OK) {
		zip->stream.total_in = 0;
		zip->stream.next_out = zip->wbuff;
		zip->stream.avail_out = sizeof(zip->wbuff);
		zip->stream.total_out = 0;
	}

	return (r);
}