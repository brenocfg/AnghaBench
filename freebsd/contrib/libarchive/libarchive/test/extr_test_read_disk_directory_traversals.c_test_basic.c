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
typedef  char wchar_t ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int AE_IFDIR ; 
 int AE_IFREG ; 
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  PATH_MAX ; 
 char* _wgetcwd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 char* archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname_w (struct archive_entry*) ; 
 int archive_entry_size (struct archive_entry*) ; 
 int archive_read_close (struct archive*) ; 
 int archive_read_data_block (struct archive*,void const**,size_t*,scalar_t__*) ; 
 int archive_read_disk_can_descend (struct archive*) ; 
 int archive_read_disk_descend (struct archive*) ; 
 struct archive* archive_read_disk_new () ; 
 int archive_read_disk_open (struct archive*,char*) ; 
 int archive_read_disk_open_w (struct archive*,char*) ; 
 int archive_read_free (struct archive*) ; 
 int archive_read_next_header2 (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int) ; 
 int /*<<< orphan*/  assertEqualMem (void const*,char*,int) ; 
 int /*<<< orphan*/  assertEqualString (char*,char*) ; 
 int /*<<< orphan*/  assertEqualWString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assertMakeDir (char*,int) ; 
 int /*<<< orphan*/  assertMakeFile (char*,int,char*) ; 
 int /*<<< orphan*/  failure (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getcwd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  wcscat (char*,char*) ; 
 char* wcschr (char*,int) ; 
 scalar_t__ wcscmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wcscpy (char*,char*) ; 
 int wcslen (char*) ; 
 char* wcsrchr (char*,int) ; 

__attribute__((used)) static void
test_basic(void)
{
	struct archive *a;
	struct archive_entry *ae;
	const void *p;
	char *initial_cwd, *cwd;
	size_t size;
	int64_t offset;
	int file_count;
#if defined(_WIN32) && !defined(__CYGWIN__)
	wchar_t *wcwd, *wp, *fullpath;
#endif

	assertMakeDir("dir1", 0755);
	assertMakeFile("dir1/file1", 0644, "0123456789");
	assertMakeFile("dir1/file2", 0644, "hello world");
	assertMakeDir("dir1/sub1", 0755);
	assertMakeFile("dir1/sub1/file1", 0644, "0123456789");
	assertMakeDir("dir1/sub2", 0755);
	assertMakeFile("dir1/sub2/file1", 0644, "0123456789");
	assertMakeFile("dir1/sub2/file2", 0644, "0123456789");
	assertMakeDir("dir1/sub2/sub1", 0755);
	assertMakeDir("dir1/sub2/sub2", 0755);
	assertMakeDir("dir1/sub2/sub3", 0755);
	assertMakeFile("dir1/sub2/sub3/file", 0644, "xyz");
	file_count = 12;

	assert((ae = archive_entry_new()) != NULL);
	assert((a = archive_read_disk_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "dir1"));

	while (file_count--) {
		assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
		if (strcmp(archive_entry_pathname(ae), "dir1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
			assertEqualInt(1, archive_read_disk_can_descend(a));
		} else if (strcmp(archive_entry_pathname(ae),
		    "dir1/file1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 10);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 10);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "0123456789", 10);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 10);
			assertEqualInt(0, archive_read_disk_can_descend(a));
		} else if (strcmp(archive_entry_pathname(ae),
		    "dir1/file2") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 11);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 11);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "hello world", 11);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 11);
			assertEqualInt(0, archive_read_disk_can_descend(a));
		} else if (strcmp(archive_entry_pathname(ae),
		    "dir1/sub1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
			assertEqualInt(1, archive_read_disk_can_descend(a));
		} else if (strcmp(archive_entry_pathname(ae),
		    "dir1/sub1/file1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 10);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 10);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "0123456789", 10);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 10);
			assertEqualInt(0, archive_read_disk_can_descend(a));
		} else if (strcmp(archive_entry_pathname(ae),
		    "dir1/sub2") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
			assertEqualInt(1, archive_read_disk_can_descend(a));
		} else if (strcmp(archive_entry_pathname(ae),
		    "dir1/sub2/file1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 10);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 10);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "0123456789", 10);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 10);
			assertEqualInt(0, archive_read_disk_can_descend(a));
		} else if (strcmp(archive_entry_pathname(ae),
		    "dir1/sub2/file2") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 10);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 10);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "0123456789", 10);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 10);
			assertEqualInt(0, archive_read_disk_can_descend(a));
		} else if (strcmp(archive_entry_pathname(ae),
		    "dir1/sub2/sub1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
			assertEqualInt(1, archive_read_disk_can_descend(a));
		} else if (strcmp(archive_entry_pathname(ae),
		    "dir1/sub2/sub2") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
			assertEqualInt(1, archive_read_disk_can_descend(a));
		} else if (strcmp(archive_entry_pathname(ae),
		    "dir1/sub2/sub3") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
			assertEqualInt(1, archive_read_disk_can_descend(a));
		} else if (strcmp(archive_entry_pathname(ae),
		    "dir1/sub2/sub3/file") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 3);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 3);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "xyz", 3);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 3);
			assertEqualInt(0, archive_read_disk_can_descend(a));
		}
		if (archive_entry_filetype(ae) == AE_IFDIR) {
			/* Descend into the current object */
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_disk_descend(a));
		}
	}
	/* There is no entry. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header2(a, ae));

	/* Close the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));

	/*
	 * Test that call archive_read_disk_open_w, wchar_t version.
	 */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open_w(a, L"dir1"));

	file_count = 12;
	while (file_count--) {
		assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
		if (wcscmp(archive_entry_pathname_w(ae), L"dir1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
			assertEqualInt(1, archive_read_disk_can_descend(a));
		} else if (wcscmp(archive_entry_pathname_w(ae),
		    L"dir1/file1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 10);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 10);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "0123456789", 10);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 10);
			assertEqualInt(0, archive_read_disk_can_descend(a));
		} else if (wcscmp(archive_entry_pathname_w(ae),
		    L"dir1/file2") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 11);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 11);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "hello world", 11);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 11);
			assertEqualInt(0, archive_read_disk_can_descend(a));
		} else if (wcscmp(archive_entry_pathname_w(ae),
		    L"dir1/sub1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
			assertEqualInt(1, archive_read_disk_can_descend(a));
		} else if (wcscmp(archive_entry_pathname_w(ae),
		    L"dir1/sub1/file1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 10);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 10);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "0123456789", 10);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 10);
			assertEqualInt(0, archive_read_disk_can_descend(a));
		} else if (wcscmp(archive_entry_pathname_w(ae),
		    L"dir1/sub2") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
			assertEqualInt(1, archive_read_disk_can_descend(a));
		} else if (wcscmp(archive_entry_pathname_w(ae),
		    L"dir1/sub2/file1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 10);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 10);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "0123456789", 10);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 10);
			assertEqualInt(0, archive_read_disk_can_descend(a));
		} else if (wcscmp(archive_entry_pathname_w(ae),
		    L"dir1/sub2/file2") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 10);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 10);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "0123456789", 10);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 10);
			assertEqualInt(0, archive_read_disk_can_descend(a));
		} else if (wcscmp(archive_entry_pathname_w(ae),
		    L"dir1/sub2/sub1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
			assertEqualInt(1, archive_read_disk_can_descend(a));
		} else if (wcscmp(archive_entry_pathname_w(ae),
		    L"dir1/sub2/sub2") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
			assertEqualInt(1, archive_read_disk_can_descend(a));
		} else if (wcscmp(archive_entry_pathname_w(ae),
		    L"dir1/sub2/sub3") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
			assertEqualInt(1, archive_read_disk_can_descend(a));
		} else if (wcscmp(archive_entry_pathname_w(ae),
		    L"dir1/sub2/sub3/file") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 3);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 3);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "xyz", 3);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 3);
			assertEqualInt(0, archive_read_disk_can_descend(a));
		}
		if (archive_entry_filetype(ae) == AE_IFDIR) {
			/* Descend into the current object */
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_disk_descend(a));
		}
	}
	/* There is no entry. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header2(a, ae));

	/* Close the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));

	/*
	 * Test that call archive_read_disk_open with a regular file.
	 */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "dir1/file1"));

	/* dir1/file1 */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
	assertEqualInt(0, archive_read_disk_can_descend(a));
	assertEqualString(archive_entry_pathname(ae), "dir1/file1");
	assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
	assertEqualInt(archive_entry_size(ae), 10);
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_data_block(a, &p, &size, &offset));
	assertEqualInt((int)size, 10);
	assertEqualInt((int)offset, 0);
	assertEqualMem(p, "0123456789", 10);

	/* There is no entry. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header2(a, ae));

	/* Close the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));


#if defined(_WIN32) && !defined(__CYGWIN__)
	/*
	 * Test for wildcard '*' or '?'
	 */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "dir1/*1"));

	/* dir1/file1 */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
	assertEqualInt(0, archive_read_disk_can_descend(a));
	assertEqualString(archive_entry_pathname(ae), "dir1/file1");
	assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
	assertEqualInt(archive_entry_size(ae), 10);
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_data_block(a, &p, &size, &offset));
	assertEqualInt((int)size, 10);
	assertEqualInt((int)offset, 0);
	assertEqualMem(p, "0123456789", 10);

	/* dir1/sub1 */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
	assertEqualInt(1, archive_read_disk_can_descend(a));
	assertEqualString(archive_entry_pathname(ae), "dir1/sub1");
	assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);

	/* Descend into the current object */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_descend(a));

	/* dir1/sub1/file1 */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
	assertEqualInt(0, archive_read_disk_can_descend(a));
	assertEqualString(archive_entry_pathname(ae), "dir1/sub1/file1");
	assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
	assertEqualInt(archive_entry_size(ae), 10);
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_data_block(a, &p, &size, &offset));
	assertEqualInt((int)size, 10);
	assertEqualInt((int)offset, 0);
	assertEqualMem(p, "0123456789", 10);

	/* There is no entry. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header2(a, ae));

	/* Close the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));

	/*
	 * Test for a full-path beginning with "//?/"
	 */
	wcwd = _wgetcwd(NULL, 0);
	fullpath = malloc(sizeof(wchar_t) * (wcslen(wcwd) + 32));
	wcscpy(fullpath, L"//?/");
	wcscat(fullpath, wcwd);
	wcscat(fullpath, L"/dir1/file1");
	free(wcwd);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open_w(a, fullpath));
	while ((wcwd = wcschr(fullpath, L'\\')) != NULL)
		*wcwd = L'/';

	/* dir1/file1 */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
	assertEqualInt(0, archive_read_disk_can_descend(a));
	assertEqualWString(archive_entry_pathname_w(ae), fullpath);
	assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
	assertEqualInt(archive_entry_size(ae), 10);
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_data_block(a, &p, &size, &offset));
	assertEqualInt((int)size, 10);
	assertEqualInt((int)offset, 0);
	assertEqualMem(p, "0123456789", 10);

	/* There is no entry. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header2(a, ae));

	/* Close the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));
	free(fullpath);

	/*
	 * Test for wild card '*' or '?' with "//?/" prefix.
	 */
	wcwd = _wgetcwd(NULL, 0);
	fullpath = malloc(sizeof(wchar_t) * (wcslen(wcwd) + 32));
	wcscpy(fullpath, L"//?/");
	wcscat(fullpath, wcwd);
	wcscat(fullpath, L"/dir1/*1");
	free(wcwd);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open_w(a, fullpath));
	while ((wcwd = wcschr(fullpath, L'\\')) != NULL)
		*wcwd = L'/';

	/* dir1/file1 */
	wp = wcsrchr(fullpath, L'/');
	wcscpy(wp+1, L"file1");
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
	assertEqualInt(0, archive_read_disk_can_descend(a));
	assertEqualWString(archive_entry_pathname_w(ae), fullpath);
	assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
	assertEqualInt(archive_entry_size(ae), 10);
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_data_block(a, &p, &size, &offset));
	assertEqualInt((int)size, 10);
	assertEqualInt((int)offset, 0);
	assertEqualMem(p, "0123456789", 10);

	/* dir1/sub1 */
	wcscpy(wp+1, L"sub1");
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
	assertEqualInt(1, archive_read_disk_can_descend(a));
	assertEqualWString(archive_entry_pathname_w(ae), fullpath);
	assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);

	/* Descend into the current object */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_descend(a));

	/* dir1/sub1/file1 */
	wcscpy(wp+1, L"sub1/file1");
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
	assertEqualInt(0, archive_read_disk_can_descend(a));
	assertEqualWString(archive_entry_pathname_w(ae), fullpath);
	assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
	assertEqualInt(archive_entry_size(ae), 10);
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_data_block(a, &p, &size, &offset));
	assertEqualInt((int)size, 10);
	assertEqualInt((int)offset, 0);
	assertEqualMem(p, "0123456789", 10);

	/* There is no entry. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header2(a, ae));

	/* Close the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));
	free(fullpath);

#endif

	/*
	 * We should be on the initial directory where we performed
	 * archive_read_disk_new() after we perform archive_read_free()
	 * even if we broke off the directory traversals.
	 */

	/* Save current working directory. */
#ifdef PATH_MAX
	initial_cwd = getcwd(NULL, PATH_MAX);/* Solaris getcwd needs the size. */
#else
	initial_cwd = getcwd(NULL, 0);
#endif

	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "dir1"));

	/* Step in a deep directory. */
	file_count = 12;
	while (file_count--) {
		assertEqualIntA(a, ARCHIVE_OK,
		    archive_read_next_header2(a, ae));
		if (strcmp(archive_entry_pathname(ae),
		    "dir1/sub1/file1") == 0)
			/*
			 * We are on an another directory at this time.
			 */
			break;
		if (archive_entry_filetype(ae) == AE_IFDIR) {
			/* Descend into the current object */
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_disk_descend(a));
		}
	}
	/* Destroy the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));

	/* We should be on the initial working directory. */
	failure(
	    "Current working directory does not return to the initial"
	    "directory");
#ifdef PATH_MAX
	cwd = getcwd(NULL, PATH_MAX);/* Solaris getcwd needs the size. */
#else
	cwd = getcwd(NULL, 0);
#endif
	assertEqualString(initial_cwd, cwd);
	free(initial_cwd);
	free(cwd);

	archive_entry_free(ae);
}