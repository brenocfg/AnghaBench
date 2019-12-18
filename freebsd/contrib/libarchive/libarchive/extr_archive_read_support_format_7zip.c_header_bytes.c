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
struct archive_read {TYPE_1__* format; } ;
struct _7zip {size_t header_bytes_remaining; size_t pack_stream_bytes_unconsumed; scalar_t__ header_is_encoded; int /*<<< orphan*/  header_crc32; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 unsigned char* __archive_read_ahead (struct archive_read*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  read_consume (struct archive_read*) ; 
 scalar_t__ read_stream (struct archive_read*,void const**,size_t,size_t) ; 

__attribute__((used)) static const unsigned char *
header_bytes(struct archive_read *a, size_t rbytes)
{
	struct _7zip *zip = (struct _7zip *)a->format->data;
	const unsigned char *p;

	if (zip->header_bytes_remaining < rbytes)
		return (NULL);
	if (zip->pack_stream_bytes_unconsumed)
		read_consume(a);

	if (zip->header_is_encoded == 0) {
		p = __archive_read_ahead(a, rbytes, NULL);
		if (p == NULL)
			return (NULL);
		zip->header_bytes_remaining -= rbytes;
		zip->pack_stream_bytes_unconsumed = rbytes;
	} else {
		const void *buff;
		ssize_t bytes;

		bytes = read_stream(a, &buff, rbytes, rbytes);
		if (bytes <= 0)
			return (NULL);
		zip->header_bytes_remaining -= bytes;
		p = buff;
	}

	/* Update checksum */
	zip->header_crc32 = crc32(zip->header_crc32, p, (unsigned)rbytes);
	return (p);
}