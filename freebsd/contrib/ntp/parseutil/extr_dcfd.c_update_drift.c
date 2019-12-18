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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LPRINTF (char*,int,...) ; 
 int R_SHIFT (int,int) ; 
 int USECSCALE ; 
 int accum_drift ; 
 int /*<<< orphan*/  asctime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,char,long,long,int /*<<< orphan*/ ) ; 
 int l_abs (long) ; 
 int /*<<< orphan*/  localtime (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
update_drift(
	     const char *drift_file,
	     long offset,
	     time_t reftime
	     )
{
	FILE *df;

	df = fopen(drift_file, "w");
	if (df != NULL)
	{
		int idrift = R_SHIFT(accum_drift, USECSCALE);
		int fdrift = accum_drift & ((1<<USECSCALE)-1);

		LPRINTF("update_drift: drift_comp %ld ", (long int)accum_drift);
		fdrift = (fdrift * 1000) / (1<<USECSCALE);
		fprintf(df, "%4d.%03d %c%ld.%06ld %.24s\n", idrift, fdrift,
			(offset < 0) ? '-' : '+', (long int)(l_abs(offset) / 1000000),
			(long int)(l_abs(offset) % 1000000), asctime(localtime(&reftime)));
		fclose(df);
		LPRINTF("update_drift: %d.%03d ppm ", idrift, fdrift);
	}
}