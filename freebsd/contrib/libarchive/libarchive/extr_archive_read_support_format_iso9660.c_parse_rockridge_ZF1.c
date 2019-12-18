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
struct file_info {int pz; unsigned char pz_log2_bs; int /*<<< orphan*/  pz_uncompressed_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_le32dec (unsigned char const*) ; 

__attribute__((used)) static void
parse_rockridge_ZF1(struct file_info *file, const unsigned char *data,
    int data_length)
{

	if (data[0] == 0x70 && data[1] == 0x7a && data_length == 12) {
		/* paged zlib */
		file->pz = 1;
		file->pz_log2_bs = data[3];
		file->pz_uncompressed_size = archive_le32dec(&data[4]);
	}
}