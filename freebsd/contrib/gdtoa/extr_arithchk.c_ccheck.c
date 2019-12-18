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
typedef  int /*<<< orphan*/  Akind ;

/* Variables and functions */
 int /*<<< orphan*/  CRAY ; 
 char* emptyfmt ; 
 scalar_t__ printf (char*,...) ; 

__attribute__((used)) static Akind *
ccheck()
{
	union {
		double d;
		long L;
		} u;
	long Cray1;

	/* Cray1 = 4617762693716115456 -- without overflow on non-Crays */
	Cray1 = printf(emptyfmt) < 0 ? 0 : 4617762;
	if (printf(emptyfmt, Cray1) >= 0)
		Cray1 = 1000000*Cray1 + 693716;
	if (printf(emptyfmt, Cray1) >= 0)
		Cray1 = 1000000*Cray1 + 115456;
	u.d = 1e13;
	if (u.L == Cray1)
		return &CRAY;
	return 0;
	}