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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_unpack (char*,size_t,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

nvlist_t *
fnvlist_unpack(char *buf, size_t buflen)
{
	nvlist_t *rv;
	VERIFY0(nvlist_unpack(buf, buflen, &rv, KM_SLEEP));
	return (rv);
}