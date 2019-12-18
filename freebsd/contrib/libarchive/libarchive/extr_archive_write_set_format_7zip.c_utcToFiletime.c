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
typedef  int uint64_t ;
typedef  int time_t ;

/* Variables and functions */
 scalar_t__ EPOC_TIME ; 

__attribute__((used)) static uint64_t
utcToFiletime(time_t t, long ns)
{
	uint64_t fileTime;

	fileTime = t;
	fileTime *= 10000000;
	fileTime += ns / 100;
	fileTime += EPOC_TIME;
	return (fileTime);
}