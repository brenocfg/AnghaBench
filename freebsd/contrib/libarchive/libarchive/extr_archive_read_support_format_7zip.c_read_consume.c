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
struct _7zip {scalar_t__ pack_stream_bytes_unconsumed; int /*<<< orphan*/  stream_offset; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,scalar_t__) ; 

__attribute__((used)) static void
read_consume(struct archive_read *a)
{
	struct _7zip *zip = (struct _7zip *)a->format->data;

	if (zip->pack_stream_bytes_unconsumed) {
		__archive_read_consume(a, zip->pack_stream_bytes_unconsumed);
		zip->stream_offset += zip->pack_stream_bytes_unconsumed;
		zip->pack_stream_bytes_unconsumed = 0;
	}
}