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
typedef  int /*<<< orphan*/  visfun_t ;

/* Variables and functions */
 int VIS_HTTPSTYLE ; 
 int VIS_MIMESTYLE ; 
 int /*<<< orphan*/  do_hvis ; 
 int /*<<< orphan*/  do_mvis ; 
 int /*<<< orphan*/  do_svis ; 

__attribute__((used)) static visfun_t
getvisfun(int flags)
{
	if (flags & VIS_HTTPSTYLE)
		return do_hvis;
	if (flags & VIS_MIMESTYLE)
		return do_mvis;
	return do_svis;
}