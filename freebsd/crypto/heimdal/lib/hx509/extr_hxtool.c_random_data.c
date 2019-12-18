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

/* Variables and functions */
 int RAND_bytes (void*,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  fwrite (void*,int,int,int /*<<< orphan*/ ) ; 
 void* malloc (int) ; 
 int parse_bytes (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int
random_data(void *opt, int argc, char **argv)
{
    void *ptr;
    int len, ret;

    len = parse_bytes(argv[0], "byte");
    if (len <= 0) {
	fprintf(stderr, "bad argument to random-data\n");
	return 1;
    }

    ptr = malloc(len);
    if (ptr == NULL) {
	fprintf(stderr, "out of memory\n");
	return 1;
    }

    ret = RAND_bytes(ptr, len);
    if (ret != 1) {
	free(ptr);
	fprintf(stderr, "did not get cryptographic strong random\n");
	return 1;
    }

    fwrite(ptr, len, 1, stdout);
    fflush(stdout);

    free(ptr);

    return 0;
}