#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* bitcount; int* buffer; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ SHA512_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BE_64_TO_8 (int*,int) ; 
 int SHA512_BLOCK_LENGTH ; 
 unsigned int SHA512_SHORT_BLOCK_LENGTH ; 
 int /*<<< orphan*/  SHA512_Transform (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,unsigned int) ; 

void
SHA512_Pad(SHA512_CTX *context)
{
	unsigned int	usedspace;

	usedspace = (context->bitcount[0] >> 3) % SHA512_BLOCK_LENGTH;
	if (usedspace > 0) {
		/* Begin padding with a 1 bit: */
		context->buffer[usedspace++] = 0x80;

		if (usedspace <= SHA512_SHORT_BLOCK_LENGTH) {
			/* Set-up for the last transform: */
			memset(&context->buffer[usedspace], 0, SHA512_SHORT_BLOCK_LENGTH - usedspace);
		} else {
			if (usedspace < SHA512_BLOCK_LENGTH) {
				memset(&context->buffer[usedspace], 0, SHA512_BLOCK_LENGTH - usedspace);
			}
			/* Do second-to-last transform: */
			SHA512_Transform(context->state, context->buffer);

			/* And set-up for the last transform: */
			memset(context->buffer, 0, SHA512_BLOCK_LENGTH - 2);
		}
	} else {
		/* Prepare for final transform: */
		memset(context->buffer, 0, SHA512_SHORT_BLOCK_LENGTH);

		/* Begin padding with a 1 bit: */
		*context->buffer = 0x80;
	}
	/* Store the length of input data (in bits) in big endian format: */
	BE_64_TO_8(&context->buffer[SHA512_SHORT_BLOCK_LENGTH],
	    context->bitcount[1]);
	BE_64_TO_8(&context->buffer[SHA512_SHORT_BLOCK_LENGTH + 8],
	    context->bitcount[0]);

	/* Final transform: */
	SHA512_Transform(context->state, context->buffer);

	/* Clean up: */
	usedspace = 0;
}