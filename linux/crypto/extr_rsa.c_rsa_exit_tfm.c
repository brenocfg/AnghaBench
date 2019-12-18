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
struct rsa_mpi_key {int dummy; } ;
struct crypto_akcipher {int dummy; } ;

/* Variables and functions */
 struct rsa_mpi_key* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 int /*<<< orphan*/  rsa_free_mpi_key (struct rsa_mpi_key*) ; 

__attribute__((used)) static void rsa_exit_tfm(struct crypto_akcipher *tfm)
{
	struct rsa_mpi_key *pkey = akcipher_tfm_ctx(tfm);

	rsa_free_mpi_key(pkey);
}