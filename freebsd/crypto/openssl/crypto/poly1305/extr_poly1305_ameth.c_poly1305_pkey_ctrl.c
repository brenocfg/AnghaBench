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

/* Variables and functions */

__attribute__((used)) static int poly1305_pkey_ctrl(EVP_PKEY *pkey, int op, long arg1, void *arg2)
{
    /* nothing, (including ASN1_PKEY_CTRL_DEFAULT_MD_NID), is supported */
    return -2;
}