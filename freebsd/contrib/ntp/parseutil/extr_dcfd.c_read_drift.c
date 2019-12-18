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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LPRINTF (char*,long,...) ; 
 int USECSCALE ; 
 int accum_drift ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fscanf (int /*<<< orphan*/ *,char*,int*,int*) ; 

__attribute__((used)) static void
read_drift(
	   const char *drift_file
	   )
{
	FILE *df;

	df = fopen(drift_file, "r");
	if (df != NULL)
	{
		int idrift = 0, fdrift = 0;

		fscanf(df, "%4d.%03d", &idrift, &fdrift);
		fclose(df);
		LPRINTF("read_drift: %d.%03d ppm ", idrift, fdrift);

		accum_drift = idrift << USECSCALE;
		fdrift     = (fdrift << USECSCALE) / 1000;
		accum_drift += fdrift & (1<<USECSCALE);
		LPRINTF("read_drift: drift_comp %ld ", (long int)accum_drift);
	}
}