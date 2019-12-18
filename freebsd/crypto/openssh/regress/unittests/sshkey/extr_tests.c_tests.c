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
 int /*<<< orphan*/  ERR_load_CRYPTO_strings () ; 
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 int /*<<< orphan*/  sshkey_file_tests () ; 
 int /*<<< orphan*/  sshkey_fuzz_tests () ; 
 int /*<<< orphan*/  sshkey_tests () ; 

void
tests(void)
{
	OpenSSL_add_all_algorithms();
	ERR_load_CRYPTO_strings();

	sshkey_tests();
	sshkey_file_tests();
	sshkey_fuzz_tests();
}