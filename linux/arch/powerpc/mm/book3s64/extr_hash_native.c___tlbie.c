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
 unsigned long ___tlbie (unsigned long,int,int,int) ; 
 int /*<<< orphan*/  trace_tlbie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __tlbie(unsigned long vpn, int psize, int apsize, int ssize)
{
	unsigned long rb;

	rb = ___tlbie(vpn, psize, apsize, ssize);
	trace_tlbie(0, 0, rb, 0, 0, 0, 0);
}