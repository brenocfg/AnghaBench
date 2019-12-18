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
struct aesctr_context_t {int dummy; } ;
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ptls_clear_memory (struct aesctr_context_t*,int) ; 

__attribute__((used)) static inline void aesctr_dispose(ptls_cipher_context_t *_ctx)
{
    struct aesctr_context_t *ctx = (struct aesctr_context_t *)_ctx;
    ptls_clear_memory(ctx, sizeof(*ctx));
}