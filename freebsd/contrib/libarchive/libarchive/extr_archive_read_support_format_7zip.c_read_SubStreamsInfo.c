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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  tmpDigests ;
struct archive_read {int dummy; } ;
struct _7z_substream_info {size_t unpack_streams; int* unpackSizes; unsigned char* digestsDefined; scalar_t__* digests; int /*<<< orphan*/ * defineds; } ;
struct _7z_folder {int numUnpackStreams; int /*<<< orphan*/  digest; scalar_t__ digest_defined; } ;
struct _7z_digests {size_t unpack_streams; int* unpackSizes; unsigned char* digestsDefined; scalar_t__* digests; int /*<<< orphan*/ * defineds; } ;

/* Variables and functions */
 size_t SIZE_MAX ; 
 size_t UMAX_ENTRY ; 
 void* calloc (size_t,int) ; 
 int folder_uncompressed_size (struct _7z_folder*) ; 
 int /*<<< orphan*/  free_Digest (struct _7z_substream_info*) ; 
 unsigned char* header_bytes (struct archive_read*,int) ; 
 int kCRC ; 
 int kEnd ; 
 int kNumUnPackStream ; 
 int kSize ; 
 int /*<<< orphan*/  memset (struct _7z_substream_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_7zip_uint64 (struct archive_read*,int*) ; 
 scalar_t__ read_Digests (struct archive_read*,struct _7z_substream_info*,scalar_t__) ; 

__attribute__((used)) static int
read_SubStreamsInfo(struct archive_read *a, struct _7z_substream_info *ss,
    struct _7z_folder *f, size_t numFolders)
{
	const unsigned char *p;
	uint64_t *usizes;
	size_t unpack_streams;
	int type;
	unsigned i;
	uint32_t numDigests;

	memset(ss, 0, sizeof(*ss));

	for (i = 0; i < numFolders; i++)
		f[i].numUnpackStreams = 1;

	if ((p = header_bytes(a, 1)) == NULL)
		return (-1);
	type = *p;

	if (type == kNumUnPackStream) {
		unpack_streams = 0;
		for (i = 0; i < numFolders; i++) {
			if (parse_7zip_uint64(a, &(f[i].numUnpackStreams)) < 0)
				return (-1);
			if (UMAX_ENTRY < f[i].numUnpackStreams)
				return (-1);
			if (unpack_streams > SIZE_MAX - UMAX_ENTRY) {
				return (-1);
			}
			unpack_streams += (size_t)f[i].numUnpackStreams;
		}
		if ((p = header_bytes(a, 1)) == NULL)
			return (-1);
		type = *p;
	} else
		unpack_streams = numFolders;

	ss->unpack_streams = unpack_streams;
	if (unpack_streams) {
		ss->unpackSizes = calloc(unpack_streams,
		    sizeof(*ss->unpackSizes));
		ss->digestsDefined = calloc(unpack_streams,
		    sizeof(*ss->digestsDefined));
		ss->digests = calloc(unpack_streams,
		    sizeof(*ss->digests));
		if (ss->unpackSizes == NULL || ss->digestsDefined == NULL ||
		    ss->digests == NULL)
			return (-1);
	}

	usizes = ss->unpackSizes;
	for (i = 0; i < numFolders; i++) {
		unsigned pack;
		uint64_t sum;

		if (f[i].numUnpackStreams == 0)
			continue;

		sum = 0;
		if (type == kSize) {
			for (pack = 1; pack < f[i].numUnpackStreams; pack++) {
				if (parse_7zip_uint64(a, usizes) < 0)
					return (-1);
				sum += *usizes++;
			}
		}
		*usizes++ = folder_uncompressed_size(&f[i]) - sum;
	}

	if (type == kSize) {
		if ((p = header_bytes(a, 1)) == NULL)
			return (-1);
		type = *p;
	}

	for (i = 0; i < unpack_streams; i++) {
		ss->digestsDefined[i] = 0;
		ss->digests[i] = 0;
	}

	numDigests = 0;
	for (i = 0; i < numFolders; i++) {
		if (f[i].numUnpackStreams != 1 || !f[i].digest_defined)
			numDigests += (uint32_t)f[i].numUnpackStreams;
	}

	if (type == kCRC) {
		struct _7z_digests tmpDigests;
		unsigned char *digestsDefined = ss->digestsDefined;
		uint32_t * digests = ss->digests;
		int di = 0;

		memset(&tmpDigests, 0, sizeof(tmpDigests));
		if (read_Digests(a, &(tmpDigests), numDigests) < 0) {
			free_Digest(&tmpDigests);
			return (-1);
		}
		for (i = 0; i < numFolders; i++) {
			if (f[i].numUnpackStreams == 1 && f[i].digest_defined) {
				*digestsDefined++ = 1;
				*digests++ = f[i].digest;
			} else {
				unsigned j;

				for (j = 0; j < f[i].numUnpackStreams;
				    j++, di++) {
					*digestsDefined++ =
					    tmpDigests.defineds[di];
					*digests++ =
					    tmpDigests.digests[di];
				}
			}
		}
		free_Digest(&tmpDigests);
		if ((p = header_bytes(a, 1)) == NULL)
			return (-1);
		type = *p;
	}

	/*
	 *  Must be kEnd.
	 */
	if (type != kEnd)
		return (-1);
	return (0);
}