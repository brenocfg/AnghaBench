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
typedef  int /*<<< orphan*/  TS_VERIFY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void TS_VERIFY_CTX_init(TS_VERIFY_CTX *ctx)
{
    OPENSSL_assert(ctx != NULL);
    memset(ctx, 0, sizeof(*ctx));
}