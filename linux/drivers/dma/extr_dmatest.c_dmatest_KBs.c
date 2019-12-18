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
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 unsigned long long FIXPT_TO_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmatest_persec (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static unsigned long long dmatest_KBs(s64 runtime, unsigned long long len)
{
	return FIXPT_TO_INT(dmatest_persec(runtime, len >> 10));
}