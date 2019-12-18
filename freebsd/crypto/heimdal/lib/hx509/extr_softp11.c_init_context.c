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
 int /*<<< orphan*/  CKR_GENERAL_ERROR ; 
 int /*<<< orphan*/  CKR_OK ; 
 int /*<<< orphan*/ * context ; 
 int hx509_context_init (int /*<<< orphan*/ **) ; 

__attribute__((used)) static CK_RV
init_context(void)
{
    if (context == NULL) {
	int ret = hx509_context_init(&context);
	if (ret)
	    return CKR_GENERAL_ERROR;
    }
    return CKR_OK;
}