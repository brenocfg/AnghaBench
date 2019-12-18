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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  DH ;

/* Variables and functions */
 int /*<<< orphan*/  DH_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_DH (int /*<<< orphan*/ *) ; 

DH *EVP_PKEY_get1_DH(EVP_PKEY *pkey)
{
    DH *ret = EVP_PKEY_get0_DH(pkey);
    if (ret != NULL)
        DH_up_ref(ret);
    return ret;
}