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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  test_r4_40_cipher_destroy () ; 
 int /*<<< orphan*/  test_r4_cipher_destroy () ; 
 int /*<<< orphan*/  test_sha_md_destroy () ; 

int openssl_destroy(ENGINE *e)
{
    test_sha_md_destroy();
#ifdef TEST_ENG_OPENSSL_RC4
    test_r4_cipher_destroy();
    test_r4_40_cipher_destroy();
#endif
    return 1;
}