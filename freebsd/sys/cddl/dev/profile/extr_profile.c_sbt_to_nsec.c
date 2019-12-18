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
typedef  int uint32_t ;
typedef  int sbintime_t ;
typedef  int hrtime_t ;

/* Variables and functions */
 int NANOSEC ; 

__attribute__((used)) static hrtime_t
sbt_to_nsec(sbintime_t sbt)
{

	return ((sbt >> 32) * NANOSEC +
	    (((uint32_t)sbt * (hrtime_t)NANOSEC) >> 32));
}