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
 int addd (double,double,double,double,int) ; 

__attribute__((used)) static int subd(double x, double y, double min, double max, int needconst) {
	return addd(x, -y, min, max, needconst);
}