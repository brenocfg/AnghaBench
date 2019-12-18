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
typedef  double u_int8_t ;
typedef  double u_int64_t ;
typedef  double u_int32_t ;
typedef  double u_int16_t ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  double int8_t ;
typedef  double int64_t ;
typedef  double int32_t ;
typedef  double int16_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*,int) ; 
 int /*<<< orphan*/  errx (int,char*,int,...) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  histcounter_size ; 
 int histcounter_type ; 
 int nsamples ; 
 double* samples ; 

void
readsamples(FILE *pfile)
{
    int		i;
    intmax_t	sample;

    if (samples == 0) {
	samples = (double *) calloc(nsamples, sizeof(double));
	if (samples == NULL)
	    errx(0, "no room for %d sample pc's", nsamples);
    }
    for (i = 0; i < nsamples; i++) {
	fread(&sample, histcounter_size, 1, pfile);
	if (feof(pfile))
		break;
	switch ( histcounter_type ) {
	case -8:
	    samples[i] += *(int8_t *)&sample;
	    break;
	case 8:
	    samples[i] += *(u_int8_t *)&sample;
	    break;
	case -16:
	    samples[i] += *(int16_t *)&sample;
	    break;
	case 16:
	    samples[i] += *(u_int16_t *)&sample;
	    break;
	case -32:
	    samples[i] += *(int32_t *)&sample;
	    break;
	case 32:
	    samples[i] += *(u_int32_t *)&sample;
	    break;
	case -64:
	    samples[i] += *(int64_t *)&sample;
	    break;
	case 64:
	    samples[i] += *(u_int64_t *)&sample;
	    break;
	default:
	    err(1, "unsupported histogram counter type %d", histcounter_type);
	}
    }
    if (i != nsamples)
	errx(1, "unexpected EOF after reading %d/%d samples", --i , nsamples );
}