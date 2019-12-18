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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * misuse_handler ; 
 int /*<<< orphan*/  printf (char*) ; 
 int sodium_init () ; 
 int /*<<< orphan*/  sodium_misuse () ; 
 int /*<<< orphan*/  sodium_runtime_has_aesni () ; 
 int /*<<< orphan*/  sodium_runtime_has_armcrypto () ; 
 int /*<<< orphan*/  sodium_runtime_has_avx () ; 
 int /*<<< orphan*/  sodium_runtime_has_avx2 () ; 
 int /*<<< orphan*/  sodium_runtime_has_avx512f () ; 
 int /*<<< orphan*/  sodium_runtime_has_neon () ; 
 int /*<<< orphan*/  sodium_runtime_has_pclmul () ; 
 int /*<<< orphan*/  sodium_runtime_has_rdrand () ; 
 int /*<<< orphan*/  sodium_runtime_has_sse2 () ; 
 int /*<<< orphan*/  sodium_runtime_has_sse3 () ; 
 int /*<<< orphan*/  sodium_runtime_has_sse41 () ; 
 int /*<<< orphan*/  sodium_runtime_has_ssse3 () ; 
 int /*<<< orphan*/  sodium_set_misuse_handler (int /*<<< orphan*/ *) ; 

int
main(void)
{
    sodium_set_misuse_handler(NULL);
    sodium_set_misuse_handler(misuse_handler);
    sodium_set_misuse_handler(NULL);

    assert(sodium_init() == 1);

    (void) sodium_runtime_has_neon();
    (void) sodium_runtime_has_armcrypto();
    (void) sodium_runtime_has_sse2();
    (void) sodium_runtime_has_sse3();
    (void) sodium_runtime_has_ssse3();
    (void) sodium_runtime_has_sse41();
    (void) sodium_runtime_has_avx();
    (void) sodium_runtime_has_avx2();
    (void) sodium_runtime_has_avx512f();
    (void) sodium_runtime_has_pclmul();
    (void) sodium_runtime_has_aesni();
    (void) sodium_runtime_has_rdrand();

    sodium_set_misuse_handler(misuse_handler);
#ifndef __EMSCRIPTEN__
    sodium_misuse();
    printf("Misuse handler returned\n");
#else
    printf("misuse_handler()\n");
#endif

    return 0;
}