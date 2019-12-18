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
 int LDNS_DIV (int,int) ; 

__attribute__((used)) static int
leap_days(int y1, int y2)
{
	--y1;
	--y2;
	return (LDNS_DIV(y2,   4) - LDNS_DIV(y1,   4)) - 
	       (LDNS_DIV(y2, 100) - LDNS_DIV(y1, 100)) +
	       (LDNS_DIV(y2, 400) - LDNS_DIV(y1, 400));
}