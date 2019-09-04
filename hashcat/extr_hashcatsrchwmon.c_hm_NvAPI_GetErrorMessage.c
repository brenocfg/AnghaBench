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
struct TYPE_3__ {int /*<<< orphan*/  (* NvAPI_GetErrorMessage ) (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  NvAPI_Status ;
typedef  int /*<<< orphan*/  NvAPI_ShortString ;
typedef  TYPE_1__ NVAPI_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hm_NvAPI_GetErrorMessage (NVAPI_PTR *nvapi, const NvAPI_Status NvAPI_rc, NvAPI_ShortString string)
{
  nvapi->NvAPI_GetErrorMessage (NvAPI_rc, string);
}