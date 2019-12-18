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
 int /*<<< orphan*/  MPASS (int) ; 
 int TDF_SBDRY ; 
 int TDF_SEINTR ; 
 int TDF_SERESTART ; 

__attribute__((used)) static int
sigdeferstop_curr_flags(int cflags)
{

	MPASS((cflags & (TDF_SEINTR | TDF_SERESTART)) == 0 ||
	    (cflags & TDF_SBDRY) != 0);
	return (cflags & (TDF_SBDRY | TDF_SEINTR | TDF_SERESTART));
}