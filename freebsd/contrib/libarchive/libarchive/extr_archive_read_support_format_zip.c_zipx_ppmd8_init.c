#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_9__ {TYPE_2__* In; } ;
struct TYPE_11__ {TYPE_1__ Stream; } ;
struct TYPE_10__ {int /*<<< orphan*/ * Read; struct archive_read* a; } ;
struct zip {int ppmd8_valid; int uncompressed_buffer_size; int decompress_init; scalar_t__ zipx_ppmd_read_compressed; int /*<<< orphan*/  entry_compressed_bytes_read; int /*<<< orphan*/ * uncompressed_buffer; TYPE_3__ ppmd8; TYPE_2__ zipx_ppmd_stream; scalar_t__ ppmd8_stream_failed; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* Ppmd8_Init ) (TYPE_3__*,int,int) ;int /*<<< orphan*/  (* Ppmd8_RangeDec_Init ) (TYPE_3__*) ;int /*<<< orphan*/  (* Ppmd8_Alloc ) (TYPE_3__*,int) ;int /*<<< orphan*/  (* Ppmd8_Construct ) (TYPE_3__*) ;int /*<<< orphan*/  (* Ppmd8_Free ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_PROGRAMMER ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_8__ __archive_ppmd8_functions ; 
 void* __archive_read_ahead (struct archive_read*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,int) ; 
 int archive_le16dec (void const*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  ppmd_read ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__*,int,int) ; 

__attribute__((used)) static int
zipx_ppmd8_init(struct archive_read *a, struct zip *zip)
{
	const void* p;
	uint32_t val;
	uint32_t order;
	uint32_t mem;
	uint32_t restore_method;

	/* Remove previous decompression context if it exists. */
	if(zip->ppmd8_valid) {
		__archive_ppmd8_functions.Ppmd8_Free(&zip->ppmd8);
		zip->ppmd8_valid = 0;
	}

	/* Create a new decompression context. */
	__archive_ppmd8_functions.Ppmd8_Construct(&zip->ppmd8);
	zip->ppmd8_stream_failed = 0;

	/* Setup function pointers required by Ppmd8 decompressor. The
	 * 'ppmd_read' function will feed new bytes to the decompressor,
	 * and will increment the 'zip->zipx_ppmd_read_compressed' counter. */
	zip->ppmd8.Stream.In = &zip->zipx_ppmd_stream;
	zip->zipx_ppmd_stream.a = a;
	zip->zipx_ppmd_stream.Read = &ppmd_read;

	/* Reset number of read bytes to 0. */
	zip->zipx_ppmd_read_compressed = 0;

	/* Read Ppmd8 header (2 bytes). */
	p = __archive_read_ahead(a, 2, NULL);
	if(!p) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated file data in PPMd8 stream");
		return (ARCHIVE_FATAL);
	}
	__archive_read_consume(a, 2);

	/* Decode the stream's compression parameters. */
	val = archive_le16dec(p);
	order = (val & 15) + 1;
	mem = ((val >> 4) & 0xff) + 1;
	restore_method = (val >> 12);

	if(order < 2 || restore_method > 2) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Invalid parameter set in PPMd8 stream (order=%d, "
		    "restore=%d)", order, restore_method);
		return (ARCHIVE_FAILED);
	}

	/* Allocate the memory needed to properly decompress the file. */
	if(!__archive_ppmd8_functions.Ppmd8_Alloc(&zip->ppmd8, mem << 20)) {
		archive_set_error(&a->archive, ENOMEM,
		    "Unable to allocate memory for PPMd8 stream: %d bytes",
		    mem << 20);
		return (ARCHIVE_FATAL);
	}

	/* Signal the cleanup function to release Ppmd8 context in the
	 * cleanup phase. */
	zip->ppmd8_valid = 1;

	/* Perform further Ppmd8 initialization. */
	if(!__archive_ppmd8_functions.Ppmd8_RangeDec_Init(&zip->ppmd8)) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
		    "PPMd8 stream range decoder initialization error");
		return (ARCHIVE_FATAL);
	}

	__archive_ppmd8_functions.Ppmd8_Init(&zip->ppmd8, order,
	    restore_method);

	/* Allocate the buffer that will hold uncompressed data. */
	free(zip->uncompressed_buffer);

	zip->uncompressed_buffer_size = 256 * 1024;
	zip->uncompressed_buffer =
	    (uint8_t*) malloc(zip->uncompressed_buffer_size);

	if(zip->uncompressed_buffer == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "No memory for PPMd8 decompression");
		return ARCHIVE_FATAL;
	}

	/* Ppmd8 initialization is done. */
	zip->decompress_init = 1;

	/* We've already read 2 bytes in the output stream. Additionally,
	 * Ppmd8 initialization code could read some data as well. So we
	 * are advancing the stream by 2 bytes plus whatever number of
	 * bytes Ppmd8 init function used. */
	zip->entry_compressed_bytes_read += 2 + zip->zipx_ppmd_read_compressed;

	return ARCHIVE_OK;
}