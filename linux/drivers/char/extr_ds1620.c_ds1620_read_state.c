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
struct therm {void* hi; void* lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  THERM_READ_TH ; 
 int /*<<< orphan*/  THERM_READ_TL ; 
 void* cvt_9_to_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds1620_in (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ds1620_read_state(struct therm *therm)
{
	therm->lo = cvt_9_to_int(ds1620_in(THERM_READ_TL, 9));
	therm->hi = cvt_9_to_int(ds1620_in(THERM_READ_TH, 9));
}