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
typedef  int u_int32_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 int f_tflag ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int thiszone ; 

__attribute__((used)) static void
printdate()
{
	struct timeval tp;
	int s;

	if (gettimeofday(&tp, NULL) == -1) {
		perror("gettimeofday");
		return;
	}

	if (f_tflag == 1) {
		/* Default */
		s = (tp.tv_sec + thiszone ) % 86400;
		(void)printf("%02d:%02d:%02d.%06u ",
		    s / 3600, (s % 3600) / 60, s % 60, (u_int32_t)tp.tv_usec);
	} else if (f_tflag > 1) {
		/* Unix timeval style */
		(void)printf("%u.%06u ",
		    (u_int32_t)tp.tv_sec, (u_int32_t)tp.tv_usec);
	}

	printf("\n");
}