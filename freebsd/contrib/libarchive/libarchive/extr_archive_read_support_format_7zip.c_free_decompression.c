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
struct archive_read {int /*<<< orphan*/  archive; } ;
struct _7zip {scalar_t__ ppmd7_valid; int /*<<< orphan*/  ppmd7_context; scalar_t__ stream_valid; int /*<<< orphan*/  stream; scalar_t__ bzstream_valid; int /*<<< orphan*/  bzstream; int /*<<< orphan*/  lzstream; scalar_t__ lzstream_valid; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* Ppmd7_Free ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ BZ2_bzDecompressEnd (int /*<<< orphan*/ *) ; 
 scalar_t__ BZ_OK ; 
 scalar_t__ Z_OK ; 
 TYPE_1__ __archive_ppmd7_functions ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ inflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
free_decompression(struct archive_read *a, struct _7zip *zip)
{
	int r = ARCHIVE_OK;

#if !defined(HAVE_ZLIB_H) &&\
	!(defined(HAVE_BZLIB_H) && defined(BZ_CONFIG_ERROR))
	(void)a;/* UNUSED */
#endif
#ifdef HAVE_LZMA_H
	if (zip->lzstream_valid)
		lzma_end(&(zip->lzstream));
#endif
#if defined(HAVE_BZLIB_H) && defined(BZ_CONFIG_ERROR)
	if (zip->bzstream_valid) {
		if (BZ2_bzDecompressEnd(&(zip->bzstream)) != BZ_OK) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "Failed to clean up bzip2 decompressor");
			r = ARCHIVE_FATAL;
		}
		zip->bzstream_valid = 0;
	}
#endif
#ifdef HAVE_ZLIB_H
	if (zip->stream_valid) {
		if (inflateEnd(&(zip->stream)) != Z_OK) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "Failed to clean up zlib decompressor");
			r = ARCHIVE_FATAL;
		}
		zip->stream_valid = 0;
	}
#endif
	if (zip->ppmd7_valid) {
		__archive_ppmd7_functions.Ppmd7_Free(
			&zip->ppmd7_context);
		zip->ppmd7_valid = 0;
	}
	return (r);
}