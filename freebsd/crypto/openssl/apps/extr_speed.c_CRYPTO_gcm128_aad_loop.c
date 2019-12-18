#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char* buf; int /*<<< orphan*/ * gcm_ctx; } ;
typedef  TYPE_1__ loopargs_t ;
typedef  int /*<<< orphan*/  GCM128_CONTEXT ;

/* Variables and functions */
 scalar_t__ COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_gcm128_aad (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 size_t D_GHASH ; 
 int /*<<< orphan*/ ** c ; 
 int /*<<< orphan*/ * lengths ; 
 size_t testnum ; 

__attribute__((used)) static int CRYPTO_gcm128_aad_loop(void *args)
{
    loopargs_t *tempargs = *(loopargs_t **) args;
    unsigned char *buf = tempargs->buf;
    GCM128_CONTEXT *gcm_ctx = tempargs->gcm_ctx;
    int count;
    for (count = 0; COND(c[D_GHASH][testnum]); count++)
        CRYPTO_gcm128_aad(gcm_ctx, buf, lengths[testnum]);
    return count;
}