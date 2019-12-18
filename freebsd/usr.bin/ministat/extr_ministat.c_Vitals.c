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
struct dataset {int n; } ;

/* Variables and functions */
 double Avg (struct dataset*) ; 
 double Max (struct dataset*) ; 
 double Median (struct dataset*) ; 
 double Min (struct dataset*) ; 
 double Stddev (struct dataset*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int* symbol ; 

__attribute__((used)) static void
Vitals(struct dataset *ds, int flag)
{

	printf("%c %3d %13.8g %13.8g %13.8g %13.8g %13.8g", symbol[flag],
	    ds->n, Min(ds), Max(ds), Median(ds), Avg(ds), Stddev(ds));
	printf("\n");
}