#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CMAC_CTX_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkey_cmac_init (TYPE_1__*) ; 

__attribute__((used)) static int pkey_cmac_copy(EVP_PKEY_CTX *dst, EVP_PKEY_CTX *src)
{
    if (!pkey_cmac_init(dst))
        return 0;
    if (!CMAC_CTX_copy(dst->data, src->data))
        return 0;
    return 1;
}