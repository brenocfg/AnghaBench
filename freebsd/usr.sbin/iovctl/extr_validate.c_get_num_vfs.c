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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOV_CONFIG_NAME ; 
 int /*<<< orphan*/  nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/ * nvlist_get_nvlist (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t
get_num_vfs(const nvlist_t *pf)
{
	const nvlist_t *iov;

	iov = nvlist_get_nvlist(pf, IOV_CONFIG_NAME);
	return (nvlist_get_number(iov, "num_vfs"));
}