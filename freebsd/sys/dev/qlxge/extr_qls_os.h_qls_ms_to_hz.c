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
 int tvtohz (struct timeval*) ; 

__attribute__((used)) static __inline int qls_ms_to_hz(int ms)
{
	int qla_hz;

	struct timeval t;

	t.tv_sec = ms / 1000;
	t.tv_usec = (ms % 1000) * 1000;

	qla_hz = tvtohz(&t);

	if (qla_hz < 0)
		qla_hz = 0x7fffffff;
	if (!qla_hz)
		qla_hz = 1;

	return (qla_hz);
}