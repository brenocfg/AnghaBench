#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
struct _7zip {scalar_t__ header_offset; } ;
struct TYPE_6__ {scalar_t__ numPackStreams; scalar_t__ pos; scalar_t__* sizes; } ;
struct TYPE_5__ {scalar_t__ numFolders; } ;
struct _7z_stream_info {TYPE_3__ pi; TYPE_2__ ci; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ read_StreamsInfo (struct archive_read*,struct _7z_stream_info*) ; 

__attribute__((used)) static int
decode_encoded_header_info(struct archive_read *a, struct _7z_stream_info *si)
{
	struct _7zip *zip = (struct _7zip *)a->format->data;

	errno = 0;
	if (read_StreamsInfo(a, si) < 0) {
		if (errno == ENOMEM)
			archive_set_error(&a->archive, -1,
			    "Couldn't allocate memory");
		else
			archive_set_error(&a->archive, -1,
			    "Malformed 7-Zip archive");
		return (ARCHIVE_FATAL);
	}

	if (si->pi.numPackStreams == 0 || si->ci.numFolders == 0) {
		archive_set_error(&a->archive, -1, "Malformed 7-Zip archive");
		return (ARCHIVE_FATAL);
	}

	if (zip->header_offset < si->pi.pos + si->pi.sizes[0] ||
	    (int64_t)(si->pi.pos + si->pi.sizes[0]) < 0 ||
	    si->pi.sizes[0] == 0 || (int64_t)si->pi.pos < 0) {
		archive_set_error(&a->archive, -1, "Malformed Header offset");
		return (ARCHIVE_FATAL);
	}

	return (ARCHIVE_OK);
}