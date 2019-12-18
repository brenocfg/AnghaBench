#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
typedef  scalar_t__ off_t ;
typedef  TYPE_1__* mpfps_t ;
struct TYPE_6__ {int length; int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPFPS_SIG ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memread (scalar_t__,TYPE_1__*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static mpfps_t
biosmptable_search_mpfps(off_t base, int length)
{
    mpfps_t mpfps;
    u_int8_t *cp, sum;
    int ofs, idx;

    mpfps = malloc(sizeof(*mpfps));
    if (mpfps == NULL) {
	warnx("unable to malloc space for MP Floating Pointer Structure");
	return (NULL);
    }
    /* search on 16-byte boundaries */
    for (ofs = 0; ofs < length; ofs += 16) {
	if (!memread(base + ofs, mpfps, sizeof(*mpfps)))
	    break;

	/* compare signature, validate checksum */
	if (!strncmp(mpfps->signature, MPFPS_SIG, strlen(MPFPS_SIG))) {
	    cp = (u_int8_t *)mpfps;
	    sum = 0;
	    /* mpfps is 16 bytes, or one "paragraph" */
	    if (mpfps->length != 1) {
	    	warnx("bad mpfps length (%d)", mpfps->length);
		continue;
	    }
	    for (idx = 0; idx < mpfps->length * 16; idx++)
		sum += *(cp + idx);
	    if (sum != 0) {
		warnx("bad mpfps checksum (%d)\n", sum);
		continue;
	    }
	    return (mpfps);
	}
    }
    free(mpfps);
    return (NULL);
}