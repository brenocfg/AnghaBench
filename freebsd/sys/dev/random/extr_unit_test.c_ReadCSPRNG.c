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
typedef  int uint8_t ;
typedef  int u_int ;
struct TYPE_2__ {int /*<<< orphan*/  (* ra_read ) (int*,int) ;int /*<<< orphan*/  (* ra_pre_read ) () ;int /*<<< orphan*/  (* ra_seeded ) () ;} ;

/* Variables and functions */
 int RANDOM_BLOCKSIZE ; 
 size_t block_deflate (int*,int*,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__ random_alg_context ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  stub4 (int*,int) ; 
 int /*<<< orphan*/  thrd_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static int
ReadCSPRNG(void *threadid)
{
	size_t tid, zsize;
	u_int buffersize;
	uint8_t *buf, *zbuf;
	int i;
#ifdef DEBUG
	int j;
#endif

	tid = (size_t)threadid;
	printf("Thread #%zd starts\n", tid);

	while (!random_alg_context.ra_seeded())
	{
		random_alg_context.ra_pre_read();
		usleep(100);
	}

	for (i = 0; i < 100000; i++) {
		buffersize = i + RANDOM_BLOCKSIZE;
		buffersize -= buffersize%RANDOM_BLOCKSIZE;
		buf = malloc(buffersize);
		zbuf = malloc(2*i + 1024);
		if (i % 1000 == 0)
			printf("Thread read %zd - %d\n", tid, i);
		if (buf != NULL && zbuf != NULL) {
			random_alg_context.ra_pre_read();
			random_alg_context.ra_read(buf, buffersize);
			zsize = block_deflate(buf, zbuf, i);
			if (zsize < i)
				printf("ERROR!! Compressible RNG output!\n");
#ifdef DEBUG
			printf("RNG output:\n");
			for (j = 0; j < i; j++) {
				printf(" %02X", buf[j]);
				if (j % 32 == 31 || j == i - 1)
					printf("\n");
			}
			printf("Compressed output:\n");
			for (j = 0; j < zsize; j++) {
				printf(" %02X", zbuf[j]);
				if (j % 32 == 31 || j == zsize - 1)
					printf("\n");
			}
#endif
			free(zbuf);
			free(buf);
		}
		usleep(100);
	}

	printf("Thread #%zd ends\n", tid);

	thrd_exit(0);

	return (0);
}