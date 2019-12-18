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
typedef  int /*<<< orphan*/  uint64_t ;
struct archive_read {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * digests; int /*<<< orphan*/ * defineds; } ;
struct _7z_pack_info {unsigned int pos; unsigned int numPackStreams; unsigned int* sizes; TYPE_1__ digest; int /*<<< orphan*/ * positions; } ;

/* Variables and functions */
 unsigned int UMAX_ENTRY ; 
 void* calloc (size_t,int) ; 
 unsigned char* header_bytes (struct archive_read*,int) ; 
 unsigned char const kEnd ; 
 unsigned char const kSize ; 
 int /*<<< orphan*/  memset (struct _7z_pack_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_7zip_uint64 (struct archive_read*,unsigned int*) ; 
 scalar_t__ read_Digests (struct archive_read*,TYPE_1__*,size_t) ; 

__attribute__((used)) static int
read_PackInfo(struct archive_read *a, struct _7z_pack_info *pi)
{
	const unsigned char *p;
	unsigned i;

	memset(pi, 0, sizeof(*pi));

	/*
	 * Read PackPos.
	 */
	if (parse_7zip_uint64(a, &(pi->pos)) < 0)
		return (-1);

	/*
	 * Read NumPackStreams.
	 */
	if (parse_7zip_uint64(a, &(pi->numPackStreams)) < 0)
		return (-1);
	if (pi->numPackStreams == 0)
		return (-1);
	if (UMAX_ENTRY < pi->numPackStreams)
		return (-1);

	/*
	 * Read PackSizes[num]
	 */
	if ((p = header_bytes(a, 1)) == NULL)
		return (-1);
	if (*p == kEnd)
		/* PackSizes[num] are not present. */
		return (0);
	if (*p != kSize)
		return (-1);
	pi->sizes = calloc((size_t)pi->numPackStreams, sizeof(uint64_t));
	pi->positions = calloc((size_t)pi->numPackStreams, sizeof(uint64_t));
	if (pi->sizes == NULL || pi->positions == NULL)
		return (-1);

	for (i = 0; i < pi->numPackStreams; i++) {
		if (parse_7zip_uint64(a, &(pi->sizes[i])) < 0)
			return (-1);
	}

	/*
	 * Read PackStreamDigests[num]
	 */
	if ((p = header_bytes(a, 1)) == NULL)
		return (-1);
	if (*p == kEnd) {
		/* PackStreamDigests[num] are not present. */
		pi->digest.defineds =
		    calloc((size_t)pi->numPackStreams, sizeof(*pi->digest.defineds));
		pi->digest.digests =
		    calloc((size_t)pi->numPackStreams, sizeof(*pi->digest.digests));
		if (pi->digest.defineds == NULL || pi->digest.digests == NULL)
			return (-1);
		return (0);
	}

	if (*p != kSize)
		return (-1);

	if (read_Digests(a, &(pi->digest), (size_t)pi->numPackStreams) < 0)
		return (-1);

	/*
	 *  Must be marked by kEnd.
	 */
	if ((p = header_bytes(a, 1)) == NULL)
		return (-1);
	if (*p != kEnd)
		return (-1);
	return (0);
}