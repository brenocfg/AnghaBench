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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDOM ; 
 int /*<<< orphan*/  ISP2 (scalar_t__) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ SPA_MINBLOCKSIZE ; 
 scalar_t__ SPA_OLD_MAXBLOCKSIZE ; 

int
zvol_check_volblocksize(uint64_t volblocksize)
{
	if (volblocksize < SPA_MINBLOCKSIZE ||
	    volblocksize > SPA_OLD_MAXBLOCKSIZE ||
	    !ISP2(volblocksize))
		return (SET_ERROR(EDOM));

	return (0);
}