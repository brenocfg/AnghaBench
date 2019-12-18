#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int tv_sec; int tv_usec; } ;
struct TYPE_3__ {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 int bytes ; 
 TYPE_2__ end ; 
 int /*<<< orphan*/  printf (char*,long long,float,int) ; 
 TYPE_1__ start ; 

__attribute__((used)) static void show_perf(void)
{
	float usec;

	usec = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

	printf("%lld bytes in %.2f seconds = %.2f Gb/sec\n",
	       (long long) bytes, usec / 1000000., (bytes * 8) / (1000. * usec));
}