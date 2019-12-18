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
typedef  int /*<<< orphan*/  HMAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  HMAC_CTX_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (int) ; 

__attribute__((used)) static HMAC_CTX *HMAC_CTX_new(void)
{
    HMAC_CTX *ctx;

    if ((ctx = OPENSSL_malloc(sizeof(*ctx))) == NULL)
        return NULL;
    HMAC_CTX_init(ctx);
    return ctx;
}