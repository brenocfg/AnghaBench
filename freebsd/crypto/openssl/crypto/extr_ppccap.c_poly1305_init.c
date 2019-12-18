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

/* Variables and functions */
 int OPENSSL_ppccap_P ; 
 int PPC_FPU ; 
 scalar_t__ poly1305_blocks ; 
 scalar_t__ poly1305_blocks_fpu ; 
 scalar_t__ poly1305_emit ; 
 scalar_t__ poly1305_emit_fpu ; 
 int /*<<< orphan*/  poly1305_init_fpu (void*,unsigned char const*) ; 
 int /*<<< orphan*/  poly1305_init_int (void*,unsigned char const*) ; 

int poly1305_init(void *ctx, const unsigned char key[16], void *func[2])
{
    if (sizeof(size_t) == 4 && (OPENSSL_ppccap_P & PPC_FPU)) {
        poly1305_init_fpu(ctx, key);
        func[0] = (void*)(uintptr_t)poly1305_blocks_fpu;
        func[1] = (void*)(uintptr_t)poly1305_emit_fpu;
    } else {
        poly1305_init_int(ctx, key);
        func[0] = (void*)(uintptr_t)poly1305_blocks;
        func[1] = (void*)(uintptr_t)poly1305_emit;
    }
    return 1;
}