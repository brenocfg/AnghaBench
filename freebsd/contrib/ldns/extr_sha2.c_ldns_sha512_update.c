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
typedef  int /*<<< orphan*/  sha2_word64 ;
typedef  int /*<<< orphan*/  const sha2_byte ;
struct TYPE_4__ {int* bitcount; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ ldns_sha512_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ADDINC128 (int*,size_t) ; 
 int LDNS_SHA512_BLOCK_LENGTH ; 
 int /*<<< orphan*/  MEMCPY_BCOPY (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ldns_sha512_Transform (TYPE_1__*,int /*<<< orphan*/ *) ; 

void ldns_sha512_update(ldns_sha512_CTX* context, const sha2_byte *data, size_t len) {
	size_t freespace, usedspace;

	if (len == 0) {
		/* Calling with no data is valid - we do nothing */
		return;
	}

	/* Sanity check: */
	assert(context != (ldns_sha512_CTX*)0 && data != (sha2_byte*)0);

	usedspace = (context->bitcount[0] >> 3) % LDNS_SHA512_BLOCK_LENGTH;
	if (usedspace > 0) {
		/* Calculate how much free space is available in the buffer */
		freespace = LDNS_SHA512_BLOCK_LENGTH - usedspace;

		if (len >= freespace) {
			/* Fill the buffer completely and process it */
			MEMCPY_BCOPY(&context->buffer[usedspace], data, freespace);
			ADDINC128(context->bitcount, freespace << 3);
			len -= freespace;
			data += freespace;
			ldns_sha512_Transform(context, (sha2_word64*)context->buffer);
		} else {
			/* The buffer is not yet full */
			MEMCPY_BCOPY(&context->buffer[usedspace], data, len);
			ADDINC128(context->bitcount, len << 3);
			/* Clean up: */
			usedspace = freespace = 0;
			return;
		}
	}
	while (len >= LDNS_SHA512_BLOCK_LENGTH) {
		/* Process as many complete blocks as we can */
		ldns_sha512_Transform(context, (sha2_word64*)data);
		ADDINC128(context->bitcount, LDNS_SHA512_BLOCK_LENGTH << 3);
		len -= LDNS_SHA512_BLOCK_LENGTH;
		data += LDNS_SHA512_BLOCK_LENGTH;
	}
	if (len > 0) {
		/* There's left-overs, so save 'em */
		MEMCPY_BCOPY(context->buffer, data, len);
		ADDINC128(context->bitcount, len << 3);
	}
	/* Clean up: */
	usedspace = freespace = 0;
}