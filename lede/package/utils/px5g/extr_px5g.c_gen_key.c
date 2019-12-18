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
typedef  int /*<<< orphan*/  mbedtls_pk_context ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_PK_RSA ; 
 int /*<<< orphan*/  _urandom ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mbedtls_pk_info_from_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_pk_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_pk_rsa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_pk_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_rsa_gen_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void gen_key(mbedtls_pk_context *key, int ksize, int exp, bool pem)
{
	mbedtls_pk_init(key);
	fprintf(stderr, "Generating RSA private key, %i bit long modulus\n", ksize);
	mbedtls_pk_setup(key, mbedtls_pk_info_from_type(MBEDTLS_PK_RSA));
	if (mbedtls_rsa_gen_key(mbedtls_pk_rsa(*key), _urandom, NULL, ksize, exp)) {
		fprintf(stderr, "error: key generation failed\n");
		exit(1);
	}
}