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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  nvpriv_t ;
struct TYPE_3__ {int nvl_nvflag; scalar_t__ nvl_pad; scalar_t__ nvl_flag; scalar_t__ nvl_priv; int /*<<< orphan*/  nvl_version; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int NV_UNIQUE_NAME ; 
 int NV_UNIQUE_NAME_TYPE ; 
 int /*<<< orphan*/  NV_VERSION ; 

__attribute__((used)) static void
nvlist_init(nvlist_t *nvl, uint32_t nvflag, nvpriv_t *priv)
{
	nvl->nvl_version = NV_VERSION;
	nvl->nvl_nvflag = nvflag & (NV_UNIQUE_NAME|NV_UNIQUE_NAME_TYPE);
	nvl->nvl_priv = (uint64_t)(uintptr_t)priv;
	nvl->nvl_flag = 0;
	nvl->nvl_pad = 0;
}