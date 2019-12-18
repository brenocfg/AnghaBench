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
 int /*<<< orphan*/  ERR_load_crypto_strings () ; 
 scalar_t__ OPENSSL_VERSION_NUMBER ; 
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 scalar_t__ OpenSSL_version_num () ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/  TT_DECLARE (char*,char*) ; 

__attribute__((used)) static void
init_ssl(void)
{
	SSL_library_init();
	ERR_load_crypto_strings();
	SSL_load_error_strings();
	OpenSSL_add_all_algorithms();
	if (OpenSSL_version_num() != OPENSSL_VERSION_NUMBER) {
		TT_DECLARE("WARN", ("Version mismatch for openssl: compiled with %lx but running with %lx", (unsigned long)OPENSSL_VERSION_NUMBER, (unsigned long) OpenSSL_version_num()));
	}
}