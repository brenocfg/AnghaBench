#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pd_handle; scalar_t__ pd_alias; } ;
typedef  TYPE_1__ pdinfo_t ;
typedef  scalar_t__ EFI_HANDLE ;

/* Variables and functions */

__attribute__((used)) static bool
same_handle(pdinfo_t *pd, EFI_HANDLE h)
{

	return (pd->pd_handle == h || pd->pd_alias == h);
}