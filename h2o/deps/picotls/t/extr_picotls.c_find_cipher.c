#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {TYPE_2__** cipher_suites; } ;
typedef  TYPE_1__ ptls_context_t ;
struct TYPE_6__ {scalar_t__ id; } ;
typedef  TYPE_2__ ptls_cipher_suite_t ;

/* Variables and functions */

__attribute__((used)) static ptls_cipher_suite_t *find_cipher(ptls_context_t *ctx, uint16_t id)
{
    ptls_cipher_suite_t **cs;
    for (cs = ctx->cipher_suites; *cs != NULL; ++cs)
        if ((*cs)->id == id)
            return *cs;
    return NULL;
}