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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  SIPHASH_CTX ;

/* Variables and functions */
 int MAXLEN ; 
 int /*<<< orphan*/  SipHash24_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SipHash_Final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SipHash_SetKey (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  SipHash_Update (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/ * vectors ; 

int
SipHash24_TestVectors(void)
{
	int i, fail = 0;
	uint8_t in[MAXLEN], out[8], k[16];
	SIPHASH_CTX ctx;

	/* Initialize key. */
	for (i = 0; i < 16; ++i)
		k[i] = i;

	/* Step through differnet length. */
	for (i = 0; i < MAXLEN; ++i) {
		in[i] = i;

		SipHash24_Init(&ctx);
		SipHash_SetKey(&ctx, k);
		SipHash_Update(&ctx, in, i);
		SipHash_Final(out, &ctx);

		if (memcmp(out, vectors[i], 8))
#if 0
			printf("%i: test vector failed\n", i);
		else
			printf("%i: test vector correct\n", i);
#else
			fail++;
#endif
	}

	return ((fail == 0));
}