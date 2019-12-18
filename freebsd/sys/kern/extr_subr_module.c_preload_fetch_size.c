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
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MODINFO_SIZE ; 
 scalar_t__ preload_search_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

size_t
preload_fetch_size(caddr_t mod)
{
	size_t *mdp;

	mdp = (size_t *)preload_search_info(mod, MODINFO_SIZE);
	if (mdp == NULL)
		return (0);
	return (*mdp);
}