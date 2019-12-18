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
struct files {int /*<<< orphan*/ ** names; scalar_t__ uncompress; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 size_t archive_read_data (struct archive*,char*,size_t const) ; 
 scalar_t__ archive_read_data_block (struct archive*,void const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 scalar_t__ archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int archive_read_open_filenames (struct archive*,int /*<<< orphan*/ **,int) ; 
 scalar_t__ archive_read_open_memory (struct archive*,char*,size_t) ; 
 scalar_t__ archive_read_support_filter_all (struct archive*) ; 
 scalar_t__ archive_read_support_format_all (struct archive*) ; 
 scalar_t__ archive_read_support_format_raw (struct archive*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertEqualInt (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,scalar_t__) ; 
 int /*<<< orphan*/  extract_reference_files (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  failure (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 char* malloc (size_t const) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 size_t rand () ; 
 char* realloc (char*,size_t) ; 
 int /*<<< orphan*/  skipping (char*,...) ; 
 char* slurpfile (size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_fuzz(const struct files *filesets)
{
	const void *blk;
	size_t blk_size;
	int64_t blk_offset;
	int n;
	const char *skip_fuzz_tests;

	skip_fuzz_tests = getenv("SKIP_TEST_FUZZ");
	if (skip_fuzz_tests != NULL) {
		skipping("Skipping fuzz tests due to SKIP_TEST_FUZZ "
		    "environment variable");
		return;
	}

	for (n = 0; filesets[n].names != NULL; ++n) {
		const size_t buffsize = 30000000;
		struct archive_entry *ae;
		struct archive *a;
		char *rawimage = NULL, *image = NULL, *tmp = NULL;
		size_t size = 0, oldsize = 0;
		int i, q;

		extract_reference_files(filesets[n].names);
		if (filesets[n].uncompress) {
			int r;
			/* Use format_raw to decompress the data. */
			assert((a = archive_read_new()) != NULL);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_support_filter_all(a));
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_support_format_raw(a));
			r = archive_read_open_filenames(a, filesets[n].names, 16384);
			if (r != ARCHIVE_OK) {
				archive_read_free(a);
				if (filesets[n].names[0] == NULL || filesets[n].names[1] == NULL) {
					skipping("Cannot uncompress fileset");
				} else {
					skipping("Cannot uncompress %s", filesets[n].names[0]);
				}
				continue;
			}
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_next_header(a, &ae));
			rawimage = malloc(buffsize);
			size = archive_read_data(a, rawimage, buffsize);
			assertEqualIntA(a, ARCHIVE_EOF,
			    archive_read_next_header(a, &ae));
			assertEqualInt(ARCHIVE_OK,
			    archive_read_free(a));
			assert(size > 0);
			if (filesets[n].names[0] == NULL || filesets[n].names[1] == NULL) {
				failure("Internal buffer is not big enough for "
					"uncompressed test files");
			} else {
				failure("Internal buffer is not big enough for "
					"uncompressed test file: %s", filesets[n].names[0]);
			}
			if (!assert(size < buffsize)) {
				free(rawimage);
				rawimage = NULL;
				continue;
			}
		} else {
			for (i = 0; filesets[n].names[i] != NULL; ++i)
			{
				char *newraw;
				tmp = slurpfile(&size, filesets[n].names[i]);
				newraw = realloc(rawimage, oldsize + size);
				if (!assert(newraw != NULL))
				{
					free(rawimage);
					rawimage = NULL;
					free(tmp);
					continue;
				}
				rawimage = newraw;
				memcpy(rawimage + oldsize, tmp, size);
				oldsize += size;
				size = oldsize;
				free(tmp);
			}
		}
		if (size == 0) {
			free(rawimage);
			rawimage = NULL;
			continue;
		}
		image = malloc(size);
		assert(image != NULL);
		if (image == NULL) {
			free(rawimage);
			rawimage = NULL;
			return;
		}

		assert(rawimage != NULL);

		srand((unsigned)time(NULL));

		for (i = 0; i < 1000; ++i) {
			FILE *f;
			int j, numbytes, trycnt;

			/* Fuzz < 1% of the bytes in the archive. */
			memcpy(image, rawimage, size);
			q = (int)size / 100;
			if (q < 4)
				q = 4;
			numbytes = (int)(rand() % q);
			for (j = 0; j < numbytes; ++j)
				image[rand() % size] = (char)rand();

			/* Save the messed-up image to a file.
			 * If we crash, that file will be useful. */
			for (trycnt = 0; trycnt < 3; trycnt++) {
				f = fopen("after.test.failure.send.this.file."
				    "to.libarchive.maintainers.with.system.details", "wb");
				if (f != NULL)
					break;
#if defined(_WIN32) && !defined(__CYGWIN__)
				/*
				 * Sometimes previous close operation does not completely
				 * end at this time. So we should take a wait while
				 * the operation running.
				 */
				Sleep(100);
#endif
			}
			assert(f != NULL);
			assertEqualInt((size_t)size, fwrite(image, 1, (size_t)size, f));
			fclose(f);

			// Try to read all headers and bodies.
			assert((a = archive_read_new()) != NULL);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_support_filter_all(a));
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_support_format_all(a));

			if (0 == archive_read_open_memory(a, image, size)) {
				while(0 == archive_read_next_header(a, &ae)) {
					while (0 == archive_read_data_block(a,
						&blk, &blk_size, &blk_offset))
						continue;
				}
				archive_read_close(a);
			}
			archive_read_free(a);

			// Just list headers, skip bodies.
			assert((a = archive_read_new()) != NULL);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_support_filter_all(a));
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_support_format_all(a));

			if (0 == archive_read_open_memory(a, image, size)) {
				while(0 == archive_read_next_header(a, &ae)) {
				}
				archive_read_close(a);
			}
			archive_read_free(a);
		}
		free(image);
		free(rawimage);
	}
}