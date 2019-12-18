#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const isc_uint8_t ;
typedef  int /*<<< orphan*/  isc_uint64_t ;
struct TYPE_4__ {int* bitcount; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ isc_sha512_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADDINC128 (int*,size_t) ; 
 int ISC_SHA512_BLOCK_LENGTH ; 
 int /*<<< orphan*/  POST (unsigned int) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  isc_sha512_transform (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

void isc_sha512_update(isc_sha512_t *context, const isc_uint8_t *data, size_t len) {
	unsigned int	freespace, usedspace;

	if (len == 0U) {
		/* Calling with no data is valid - we do nothing */
		return;
	}

	/* Sanity check: */
	REQUIRE(context != (isc_sha512_t *)0 && data != (isc_uint8_t*)0);

	usedspace = (unsigned int)((context->bitcount[0] >> 3) %
				   ISC_SHA512_BLOCK_LENGTH);
	if (usedspace > 0) {
		/* Calculate how much free space is available in the buffer */
		freespace = ISC_SHA512_BLOCK_LENGTH - usedspace;

		if (len >= freespace) {
			/* Fill the buffer completely and process it */
			memcpy(&context->buffer[usedspace], data, freespace);
			ADDINC128(context->bitcount, freespace << 3);
			len -= freespace;
			data += freespace;
			isc_sha512_transform(context,
					     (isc_uint64_t*)context->buffer);
		} else {
			/* The buffer is not yet full */
			memcpy(&context->buffer[usedspace], data, len);
			ADDINC128(context->bitcount, len << 3);
			/* Clean up: */
			usedspace = freespace = 0;
			/* Avoid compiler warnings: */
			POST(usedspace); POST(freespace);
			return;
		}
	}
	while (len >= ISC_SHA512_BLOCK_LENGTH) {
		/* Process as many complete blocks as we can */
		memcpy(context->buffer, data, ISC_SHA512_BLOCK_LENGTH);
		isc_sha512_transform(context, (isc_uint64_t*)context->buffer);
		ADDINC128(context->bitcount, ISC_SHA512_BLOCK_LENGTH << 3);
		len -= ISC_SHA512_BLOCK_LENGTH;
		data += ISC_SHA512_BLOCK_LENGTH;
	}
	if (len > 0U) {
		/* There's left-overs, so save 'em */
		memcpy(context->buffer, data, len);
		ADDINC128(context->bitcount, len << 3);
	}
	/* Clean up: */
	usedspace = freespace = 0;
	/* Avoid compiler warnings: */
	POST(usedspace); POST(freespace);
}