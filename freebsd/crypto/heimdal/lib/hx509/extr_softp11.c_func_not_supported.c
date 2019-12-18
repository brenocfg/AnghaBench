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
typedef  int /*<<< orphan*/  CK_RV ;

/* Variables and functions */
 int /*<<< orphan*/  CKR_FUNCTION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  st_logf (char*) ; 

__attribute__((used)) static CK_RV
func_not_supported(void)
{
    st_logf("function not supported\n");
    return CKR_FUNCTION_NOT_SUPPORTED;
}