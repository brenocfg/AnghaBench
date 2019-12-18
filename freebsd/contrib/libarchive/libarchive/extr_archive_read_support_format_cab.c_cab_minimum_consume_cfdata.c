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
typedef  scalar_t__ uint16_t ;
struct cfdata {scalar_t__ unconsumed; scalar_t__ read_offset; scalar_t__ uncompressed_avail; scalar_t__ compressed_bytes_remaining; int /*<<< orphan*/  uncompressed_bytes_remaining; } ;
struct cab {int /*<<< orphan*/  cab_offset; TYPE_2__* entry_cffolder; struct cfdata* entry_cfdata; } ;
struct archive_read {TYPE_1__* format; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {scalar_t__ comptype; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ COMPTYPE_NONE ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,scalar_t__) ; 
 int cab_checksum_finish (struct archive_read*) ; 
 int /*<<< orphan*/  cab_checksum_update (struct archive_read*,size_t) ; 

__attribute__((used)) static int64_t
cab_minimum_consume_cfdata(struct archive_read *a, int64_t consumed_bytes)
{
	struct cab *cab = (struct cab *)(a->format->data);
	struct cfdata *cfdata;
	int64_t cbytes, rbytes;
	int err;

	cfdata = cab->entry_cfdata;
	rbytes = consumed_bytes;
	if (cab->entry_cffolder->comptype == COMPTYPE_NONE) {
		if (consumed_bytes < cfdata->unconsumed)
			cbytes = consumed_bytes;
		else
			cbytes = cfdata->unconsumed;
		rbytes -= cbytes; 
		cfdata->read_offset += (uint16_t)cbytes;
		cfdata->uncompressed_bytes_remaining -= (uint16_t)cbytes;
		cfdata->unconsumed -= cbytes;
	} else {
		cbytes = cfdata->uncompressed_avail - cfdata->read_offset;
		if (cbytes > 0) {
			if (consumed_bytes < cbytes)
				cbytes = consumed_bytes;
			rbytes -= cbytes;
			cfdata->read_offset += (uint16_t)cbytes;
			cfdata->uncompressed_bytes_remaining -= (uint16_t)cbytes;
		}

		if (cfdata->unconsumed) {
			cbytes = cfdata->unconsumed;
			cfdata->unconsumed = 0;
		} else
			cbytes = 0;
	}
	if (cbytes) {
		/* Compute the sum. */
		cab_checksum_update(a, (size_t)cbytes);

		/* Consume as much as the compressor actually used. */
		__archive_read_consume(a, cbytes);
		cab->cab_offset += cbytes;
		cfdata->compressed_bytes_remaining -= (uint16_t)cbytes;
		if (cfdata->compressed_bytes_remaining == 0) {
			err = cab_checksum_finish(a);
			if (err < 0)
				return (err);
		}
	}
	return (rbytes);
}