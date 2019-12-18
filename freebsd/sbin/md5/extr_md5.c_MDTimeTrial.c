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
struct timeval {float tv_sec; scalar_t__ tv_usec; } ;
struct rusage {int /*<<< orphan*/  ru_utime; } ;
struct TYPE_3__ {char* name; char* (* End ) (int /*<<< orphan*/ *,char*) ;int /*<<< orphan*/  (* Update ) (int /*<<< orphan*/ *,unsigned char*,int) ;int /*<<< orphan*/  (* Init ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  DIGEST_CTX ;
typedef  TYPE_1__ Algorithm_t ;

/* Variables and functions */
 int HEX_DIGEST_LENGTH ; 
 int /*<<< orphan*/  RUSAGE_SELF ; 
 int TEST_BLOCK_COUNT ; 
 int TEST_BLOCK_LEN ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getrusage (int /*<<< orphan*/ ,struct rusage*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,unsigned char*,int) ; 
 char* stub3 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  timersub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static void
MDTimeTrial(const Algorithm_t *alg)
{
	DIGEST_CTX context;
	struct rusage before, after;
	struct timeval total;
	float seconds;
	unsigned char block[TEST_BLOCK_LEN];
	unsigned int i;
	char *p, buf[HEX_DIGEST_LENGTH];

	printf("%s time trial. Digesting %d %d-byte blocks ...",
	    alg->name, TEST_BLOCK_COUNT, TEST_BLOCK_LEN);
	fflush(stdout);

	/* Initialize block */
	for (i = 0; i < TEST_BLOCK_LEN; i++)
		block[i] = (unsigned char) (i & 0xff);

	/* Start timer */
	getrusage(RUSAGE_SELF, &before);

	/* Digest blocks */
	alg->Init(&context);
	for (i = 0; i < TEST_BLOCK_COUNT; i++)
		alg->Update(&context, block, TEST_BLOCK_LEN);
	p = alg->End(&context, buf);

	/* Stop timer */
	getrusage(RUSAGE_SELF, &after);
	timersub(&after.ru_utime, &before.ru_utime, &total);
	seconds = total.tv_sec + (float) total.tv_usec / 1000000;

	printf(" done\n");
	printf("Digest = %s", p);
	printf("\nTime = %f seconds\n", seconds);
	printf("Speed = %f MiB/second\n", (float) TEST_BLOCK_LEN * 
		(float) TEST_BLOCK_COUNT / seconds / (1 << 20));
}