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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ ibnd_is_xsigo_hca (int /*<<< orphan*/ ) ; 
 scalar_t__ ibnd_is_xsigo_tca (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_xsigo_ca(uint64_t guid)
{
	if (ibnd_is_xsigo_hca(guid) || ibnd_is_xsigo_tca(guid))
		return 1;
	else
		return 0;
}