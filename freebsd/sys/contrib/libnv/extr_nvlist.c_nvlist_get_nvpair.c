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
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NV_TYPE_NONE ; 
 int /*<<< orphan*/  const* nvlist_find (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*) ; 

const nvpair_t *
nvlist_get_nvpair(const nvlist_t *nvl, const char *name)
{

	return (nvlist_find(nvl, NV_TYPE_NONE, name));
}