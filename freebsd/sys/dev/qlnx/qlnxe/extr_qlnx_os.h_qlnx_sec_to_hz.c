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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 int tvtohz (struct timeval*) ; 

__attribute__((used)) static __inline int qlnx_sec_to_hz(int sec)
{
	struct timeval t;

	t.tv_sec = sec;
	t.tv_usec = 0;

	return (tvtohz(&t));
}