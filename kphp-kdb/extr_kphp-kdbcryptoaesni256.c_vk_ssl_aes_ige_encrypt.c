#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  key; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
typedef  TYPE_2__ vk_aes_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  AES_ENCRYPT ; 
 int /*<<< orphan*/  AES_ige_encrypt (unsigned char const*,unsigned char*,int,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vk_ssl_aes_ige_encrypt (vk_aes_ctx_t *ctx, const unsigned char *in, unsigned char *out, int size, unsigned char iv[32]){
  AES_ige_encrypt (in, out, size, &ctx->u.key, iv, AES_ENCRYPT);
}