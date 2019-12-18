#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct zip {int ppmd8_stream_failed; int /*<<< orphan*/  zipx_ppmd_read_compressed; } ;
struct archive_read {TYPE_1__* format; } ;
typedef  int ssize_t ;
struct TYPE_4__ {struct archive_read* a; } ;
struct TYPE_3__ {scalar_t__ data; } ;
typedef  TYPE_2__ IByteIn ;
typedef  int /*<<< orphan*/  const Byte ;

/* Variables and functions */
 int /*<<< orphan*/ * __archive_read_ahead (struct archive_read*,int,int*) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,int) ; 

__attribute__((used)) static Byte
ppmd_read(void* p) {
	/* Get the handle to current decompression context. */
	struct archive_read *a = ((IByteIn*)p)->a;
	struct zip *zip = (struct zip*) a->format->data;
	ssize_t bytes_avail = 0;

	/* Fetch next byte. */
	const uint8_t* data = __archive_read_ahead(a, 1, &bytes_avail);
	if(bytes_avail < 1) {
		zip->ppmd8_stream_failed = 1;
		return 0;
	}

	__archive_read_consume(a, 1);

	/* Increment the counter. */
	++zip->zipx_ppmd_read_compressed;

	/* Return the next compressed byte. */
	return data[0];
}