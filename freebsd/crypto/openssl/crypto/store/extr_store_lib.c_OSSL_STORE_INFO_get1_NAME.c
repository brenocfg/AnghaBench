#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__ name; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ _; } ;
typedef  TYPE_3__ OSSL_STORE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 char* OPENSSL_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_STORE_F_OSSL_STORE_INFO_GET1_NAME ; 
 scalar_t__ OSSL_STORE_INFO_NAME ; 
 int /*<<< orphan*/  OSSL_STORE_R_NOT_A_NAME ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *OSSL_STORE_INFO_get1_NAME(const OSSL_STORE_INFO *info)
{
    if (info->type == OSSL_STORE_INFO_NAME) {
        char *ret = OPENSSL_strdup(info->_.name.name);

        if (ret == NULL)
            OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_INFO_GET1_NAME,
                          ERR_R_MALLOC_FAILURE);
        return ret;
    }
    OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_INFO_GET1_NAME,
                  OSSL_STORE_R_NOT_A_NAME);
    return NULL;
}