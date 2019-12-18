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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  vfp_double_packed_abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfp_get_double (int) ; 
 int /*<<< orphan*/  vfp_put_double (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 vfp_double_fabs(int dd, int unused, int dm, u32 fpscr)
{
	vfp_put_double(vfp_double_packed_abs(vfp_get_double(dm)), dd);
	return 0;
}