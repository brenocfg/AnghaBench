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
typedef  scalar_t__ uint64_t ;
typedef  unsigned int uint32_t ;
struct archive_read {TYPE_1__* format; } ;
struct _7zip {scalar_t__ header_offset; } ;
struct TYPE_6__ {unsigned int numFolders; struct _7z_folder* folders; } ;
struct TYPE_5__ {scalar_t__* sizes; scalar_t__ pos; unsigned int numPackStreams; scalar_t__* positions; } ;
struct _7z_stream_info {TYPE_3__ ci; int /*<<< orphan*/  ss; TYPE_2__ pi; } ;
struct _7z_folder {unsigned int packIndex; scalar_t__ numPackedStreams; } ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 unsigned char* header_bytes (struct archive_read*,int) ; 
 unsigned char const kEnd ; 
 unsigned char const kPackInfo ; 
 unsigned char const kSubStreamsInfo ; 
 unsigned char const kUnPackInfo ; 
 int /*<<< orphan*/  memset (struct _7z_stream_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ read_CodersInfo (struct archive_read*,TYPE_3__*) ; 
 scalar_t__ read_PackInfo (struct archive_read*,TYPE_2__*) ; 
 scalar_t__ read_SubStreamsInfo (struct archive_read*,int /*<<< orphan*/ *,struct _7z_folder*,size_t) ; 

__attribute__((used)) static int
read_StreamsInfo(struct archive_read *a, struct _7z_stream_info *si)
{
	struct _7zip *zip = (struct _7zip *)a->format->data;
	const unsigned char *p;
	unsigned i;

	memset(si, 0, sizeof(*si));

	if ((p = header_bytes(a, 1)) == NULL)
		return (-1);
	if (*p == kPackInfo) {
		uint64_t packPos;

		if (read_PackInfo(a, &(si->pi)) < 0)
			return (-1);

		if (si->pi.positions == NULL || si->pi.sizes == NULL)
			return (-1);
		/*
		 * Calculate packed stream positions.
		 */
		packPos = si->pi.pos;
		for (i = 0; i < si->pi.numPackStreams; i++) {
			si->pi.positions[i] = packPos;
			packPos += si->pi.sizes[i];
			if (packPos > zip->header_offset)
				return (-1);
		}
		if ((p = header_bytes(a, 1)) == NULL)
			return (-1);
	}
	if (*p == kUnPackInfo) {
		uint32_t packIndex;
		struct _7z_folder *f;

		if (read_CodersInfo(a, &(si->ci)) < 0)
			return (-1);

		/*
		 * Calculate packed stream indexes.
		 */
		packIndex = 0;
		f = si->ci.folders;
		for (i = 0; i < si->ci.numFolders; i++) {
			f[i].packIndex = packIndex;
			packIndex += (uint32_t)f[i].numPackedStreams;
			if (packIndex > si->pi.numPackStreams)
				return (-1);
		}
		if ((p = header_bytes(a, 1)) == NULL)
			return (-1);
	}

	if (*p == kSubStreamsInfo) {
		if (read_SubStreamsInfo(a, &(si->ss),
		    si->ci.folders, (size_t)si->ci.numFolders) < 0)
			return (-1);
		if ((p = header_bytes(a, 1)) == NULL)
			return (-1);
	}

	/*
	 *  Must be kEnd.
	 */
	if (*p != kEnd)
		return (-1);
	return (0);
}