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
typedef  long time_t ;
typedef  int /*<<< orphan*/  MD_CTX ;

/* Variables and functions */
 int MD ; 
 int /*<<< orphan*/  MDFinal (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDPrint (unsigned char*) ; 
 int /*<<< orphan*/  MDUpdate (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int TEST_BLOCK_COUNT ; 
 int TEST_BLOCK_LEN ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  time (long*) ; 

__attribute__((used)) static void MDTimeTrial(void)
{
  MD_CTX context;
  time_t endTime, startTime;
  unsigned char block[TEST_BLOCK_LEN], digest[16];
  unsigned int i;

  printf("MD%d time trial. Digesting %d %d-byte blocks ...",
         MD, TEST_BLOCK_LEN, TEST_BLOCK_COUNT);

  /* Initialize block */
  for (i = 0; i < TEST_BLOCK_LEN; i++)
    block[i] = (unsigned char)(i & 0xff);

  /* Start timer */
  time(&startTime);

  /* Digest blocks */
  MDInit(&context);
  for (i = 0; i < TEST_BLOCK_COUNT; i++)
    MDUpdate(&context, block, TEST_BLOCK_LEN);
  MDFinal(digest, &context);

  /* Stop timer */
  time(&endTime);

  printf(" done\n");
  printf("Digest = ");
  MDPrint(digest);
  printf("\nTime = %ld seconds\n", (long)(endTime-startTime));
  printf("Speed = %ld bytes/second\n",
         (long)TEST_BLOCK_LEN * (long)TEST_BLOCK_COUNT/(endTime-startTime));
}