#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cb; } ;
struct TYPE_7__ {int /*<<< orphan*/  key; TYPE_1__ super; } ;
typedef  TYPE_2__ ptls_minicrypto_secp256r1sha256_sign_certificate_t ;
struct TYPE_8__ {int len; int /*<<< orphan*/  base; } ;
typedef  TYPE_3__ ptls_iovec_t ;

/* Variables and functions */
 int PTLS_ERROR_INCOMPATIBLE_KEY ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  secp256r1sha256_sign ; 

int ptls_minicrypto_init_secp256r1sha256_sign_certificate(ptls_minicrypto_secp256r1sha256_sign_certificate_t *self,
                                                          ptls_iovec_t key)
{
    if (key.len != sizeof(self->key))
        return PTLS_ERROR_INCOMPATIBLE_KEY;

    self->super.cb = secp256r1sha256_sign;
    memcpy(self->key, key.base, sizeof(self->key));

    return 0;
}