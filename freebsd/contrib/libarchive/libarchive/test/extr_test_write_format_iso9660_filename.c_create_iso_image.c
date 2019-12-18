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
typedef  int /*<<< orphan*/  sym255 ;
typedef  int /*<<< orphan*/  sym128 ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  add_entry (struct archive*,char*,char*) ; 
 scalar_t__ archive_write_add_filter_none (struct archive*) ; 
 int /*<<< orphan*/  archive_write_close (struct archive*) ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 struct archive* archive_write_new () ; 
 scalar_t__ archive_write_open_memory (struct archive*,unsigned char*,size_t,size_t*) ; 
 scalar_t__ archive_write_set_bytes_in_last_block (struct archive*,int) ; 
 scalar_t__ archive_write_set_bytes_per_block (struct archive*,int) ; 
 scalar_t__ archive_write_set_format_iso9660 (struct archive*) ; 
 scalar_t__ archive_write_set_option (struct archive*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ archive_write_set_options (struct archive*,char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertA (int) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
create_iso_image(unsigned char *buff, size_t buffsize, size_t *used,
    const char *opt)
{
	struct archive *a;
	int i, l, fcnt;
	const int lens[] = {
	    0, 1, 3, 5, 7, 8, 9, 29, 30, 31, 32,
		62, 63, 64, 65, 101, 102, 103, 104,
	    191, 192, 193, 194, 204, 205, 206, 207, 208,
		252, 253, 254, 255,
	    -1 };
	char fname1[256];
	char fname2[256];
	char sym1[2];
	char sym128[129];
	char sym255[256];

	/* ISO9660 format: Create a new archive in memory. */
	assert((a = archive_write_new()) != NULL);
	assertA(0 == archive_write_set_format_iso9660(a));
	assertA(0 == archive_write_add_filter_none(a));
	assertA(0 == archive_write_set_option(a, NULL, "pad", NULL));
	if (opt)
		assertA(0 == archive_write_set_options(a, opt));
	assertA(0 == archive_write_set_bytes_per_block(a, 1));
	assertA(0 == archive_write_set_bytes_in_last_block(a, 1));
	assertA(0 == archive_write_open_memory(a, buff, buffsize, used));

	sym1[0] = 'x';
	sym1[1] = '\0';
	for (i = 0; i < (int)sizeof(sym128)-2; i++)
		sym128[i] = 'a';
	sym128[sizeof(sym128)-2] = 'x';
	sym128[sizeof(sym128)-1] = '\0';
	for (i = 0; i < (int)sizeof(sym255)-2; i++)
		sym255[i] = 'a';
	sym255[sizeof(sym255)-2] = 'x';
	sym255[sizeof(sym255)-1] = '\0';

	fcnt = 0;
	for (i = 0; lens[i] >= 0; i++) {
		for (l = 0; l < lens[i]; l++) {
			fname1[l] = 'a';
			fname2[l] = 'A';
		}
		if (l > 0) {
			fname1[l] = '\0';
			fname2[l] = '\0';
			add_entry(a, fname1, NULL);
			add_entry(a, fname2, sym1);
			fcnt += 2;
		}
		if (l < 254) {
			fname1[l] = '.';
			fname1[l+1] = 'c';
			fname1[l+2] = '\0';
			fname2[l] = '.';
			fname2[l+1] = 'C';
			fname2[l+2] = '\0';
			add_entry(a, fname1, sym128);
			add_entry(a, fname2, sym255);
			fcnt += 2;
		}
		if (l < 252) {
			fname1[l] = '.';
			fname1[l+1] = 'p';
			fname1[l+2] = 'n';
			fname1[l+3] = 'g';
			fname1[l+4] = '\0';
			fname2[l] = '.';
			fname2[l+1] = 'P';
			fname2[l+2] = 'N';
			fname2[l+3] = 'G';
			fname2[l+4] = '\0';
			add_entry(a, fname1, NULL);
			add_entry(a, fname2, sym1);
			fcnt += 2;
		}
		if (l < 251) {
			fname1[l] = '.';
			fname1[l+1] = 'j';
			fname1[l+2] = 'p';
			fname1[l+3] = 'e';
			fname1[l+4] = 'g';
			fname1[l+5] = '\0';
			fname2[l] = '.';
			fname2[l+1] = 'J';
			fname2[l+2] = 'P';
			fname2[l+3] = 'E';
			fname2[l+4] = 'G';
			fname2[l+5] = '\0';
			add_entry(a, fname1, sym128);
			add_entry(a, fname2, sym255);
			fcnt += 2;
		}
	}

	/* Close out the archive. */
	assertEqualIntA(a, ARCHIVE_OK, archive_write_close(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_write_free(a));

	return (fcnt);
}