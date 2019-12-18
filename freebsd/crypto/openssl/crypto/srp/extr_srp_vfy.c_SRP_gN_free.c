#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bn; struct TYPE_4__* b64_bn; } ;
typedef  TYPE_1__ SRP_gN_cache ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

__attribute__((used)) static void SRP_gN_free(SRP_gN_cache *gN_cache)
{
    if (gN_cache == NULL)
        return;
    OPENSSL_free(gN_cache->b64_bn);
    BN_free(gN_cache->bn);
    OPENSSL_free(gN_cache);
}