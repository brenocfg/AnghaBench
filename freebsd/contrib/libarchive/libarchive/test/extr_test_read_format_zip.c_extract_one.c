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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ la_ssize_t ;

/* Variables and functions */
 scalar_t__ archive_entry_size (struct archive_entry*) ; 
 scalar_t__ archive_read_data (struct archive*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  assertEqualInt (scalar_t__,scalar_t__) ; 
 scalar_t__ crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 

__attribute__((used)) static
int extract_one(struct archive* a, struct archive_entry* ae, uint32_t crc)
{
	la_ssize_t fsize, bytes_read;
	uint8_t* buf;
	int ret = 1;
	uint32_t computed_crc;

	fsize = (la_ssize_t) archive_entry_size(ae);
	buf = malloc(fsize);
	if(buf == NULL)
		return 1;

	bytes_read = archive_read_data(a, buf, fsize);
	if(bytes_read != fsize) {
		assertEqualInt(bytes_read, fsize);
		goto fn_exit;
	}

	computed_crc = crc32(0, buf, fsize);
	assertEqualInt(computed_crc, crc);
	ret = 0;

fn_exit:
	free(buf);
	return ret;
}