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
typedef  int u_long ;

/* Variables and functions */
 int NBUCKETS ; 
 int NOPS ; 
 int NSIZE ; 
 int** foo ; 
 int /*<<< orphan*/  free (int*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,...) ; 
 int random () ; 
 int* realloc (int*,int) ; 
 int /*<<< orphan*/  sbrk (int /*<<< orphan*/ ) ; 
 int strtoul (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv) 
{
    u_long i,j,k;
    
    if (argc > 1) NOPS     = strtoul(argv[1],0,0);
    if (argc > 2) NBUCKETS = strtoul(argv[2],0,0);
    if (argc > 3) NSIZE	   = strtoul(argv[3],0,0);
    printf("BRK(0)=%p ", sbrk(0));
    foo = malloc(sizeof(*foo) * NBUCKETS);
    memset(foo, 0, sizeof(*foo) * NBUCKETS);
    for (i = 1; i <= 4096; i *= 2) {
        for (j = 0; j < 40960/i && j < NBUCKETS; j++) {
	    foo[j] = malloc(i);
        }
        for (j = 0; j < 40960/i && j < NBUCKETS; j++) {
	    free(foo[j]);
	    foo[j] = NULL;
        }
    }

    for (i = 0; i < NOPS; i++) {
	j = random() % NBUCKETS;
	k = random() % NSIZE;
	foo[j] = realloc(foo[j], k & 1 ? 0 : k);
	if (k & 1 || k == 0) {
		/*
		 * Workaround because realloc return bogus pointer rather than
		 * NULL if passed zero length.
		 */
		foo[j] = NULL;
	}
	if (foo[j])
	    foo[j][0] = 1;
    }
    printf("BRK(1)=%p ", sbrk(0));
    for (j = 0; j < NBUCKETS; j++) {
	if (foo[j]) {
	    free(foo[j]);
	    foo[j] = NULL;
	}
    }
    printf("BRK(2)=%p NOPS=%lu NBUCKETS=%lu NSIZE=%lu\n",
	sbrk(0), NOPS, NBUCKETS, NSIZE);
    return 0;
}