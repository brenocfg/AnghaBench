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
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,long,char*,float,int,float,char*) ; 
 scalar_t__ verbose ; 

void
ptransfer (char *direction, long int bytes,
	   struct timeval * t0, struct timeval * t1)
{
    struct timeval td;
    float s;
    float bs;
    int prec;
    char *unit;

    if (verbose) {
	td.tv_sec = t1->tv_sec - t0->tv_sec;
	td.tv_usec = t1->tv_usec - t0->tv_usec;
	if (td.tv_usec < 0) {
	    td.tv_sec--;
	    td.tv_usec += 1000000;
	}
	s = td.tv_sec + (td.tv_usec / 1000000.);
	bs = bytes / (s ? s : 1);
	if (bs >= 1048576) {
	    bs /= 1048576;
	    unit = "M";
	    prec = 2;
	} else if (bs >= 1024) {
	    bs /= 1024;
	    unit = "k";
	    prec = 1;
	} else {
	    unit = "";
	    prec = 0;
	}

	printf ("%ld bytes %s in %.3g seconds (%.*f %sbyte/s)\n",
		bytes, direction, s, prec, bs, unit);
    }
}