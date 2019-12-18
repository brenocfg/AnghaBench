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
typedef  int /*<<< orphan*/  teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  TP_SETBELLPD ; 
 int /*<<< orphan*/  teken_funcs_param (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
teken_subr_cons25_set_bell_pitch_duration(const teken_t *t, unsigned int pitch,
    unsigned int duration)
{

	teken_funcs_param(t, TP_SETBELLPD, (pitch << 16) |
	    (duration & 0xffff));
}