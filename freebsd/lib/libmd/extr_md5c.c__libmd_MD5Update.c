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
typedef  int u_int32_t ;
struct TYPE_3__ {int* count; unsigned char const* buffer; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Transform (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,unsigned int) ; 

void
MD5Update (MD5_CTX *context, const void *in, unsigned int inputLen)
{
	unsigned int i, idx, partLen;
	const unsigned char *input = in;

	/* Compute number of bytes mod 64 */
	idx = (unsigned int)((context->count[0] >> 3) & 0x3F);

	/* Update number of bits */
	if ((context->count[0] += ((u_int32_t)inputLen << 3))
	    < ((u_int32_t)inputLen << 3))
		context->count[1]++;
	context->count[1] += ((u_int32_t)inputLen >> 29);

	partLen = 64 - idx;

	/* Transform as many times as possible. */
	if (inputLen >= partLen) {
		memcpy((void *)&context->buffer[idx], (const void *)input,
		    partLen);
		MD5Transform (context->state, context->buffer);

		for (i = partLen; i + 63 < inputLen; i += 64)
			MD5Transform (context->state, &input[i]);

		idx = 0;
	}
	else
		i = 0;

	/* Buffer remaining input */
	memcpy ((void *)&context->buffer[idx], (const void *)&input[i],
	    inputLen-i);
}