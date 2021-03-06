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
typedef  int /*<<< orphan*/  ksiginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  ksiginfo_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ksiginfo_free(ksiginfo_t *ksi)
{
	uma_zfree(ksiginfo_zone, ksi);
}