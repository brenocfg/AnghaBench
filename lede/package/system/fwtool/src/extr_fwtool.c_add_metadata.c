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
struct fwimage_trailer {int size; int /*<<< orphan*/  type; } ;
struct fwimage_header {int dummy; } ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int /*<<< orphan*/  FWIMAGE_INFO ; 
 int /*<<< orphan*/  METADATA_MAXLEN ; 
 scalar_t__ append_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fwimage_trailer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_trailer (int /*<<< orphan*/ ,struct fwimage_trailer*) ; 
 int /*<<< orphan*/  firmware_file ; 
 int /*<<< orphan*/  fwrite (struct fwimage_header*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metadata_file ; 
 int /*<<< orphan*/  trailer_update_crc (struct fwimage_trailer*,struct fwimage_header*,int) ; 

__attribute__((used)) static int
add_metadata(struct fwimage_trailer *tr)
{
	struct fwimage_header hdr = {};

	tr->type = FWIMAGE_INFO;
	tr->size = sizeof(hdr) + sizeof(*tr);

	trailer_update_crc(tr, &hdr, sizeof(hdr));
	fwrite(&hdr, sizeof(hdr), 1, firmware_file);

	if (append_data(metadata_file, firmware_file, tr, METADATA_MAXLEN))
		return 1;

	append_trailer(firmware_file, tr);

	return 0;
}