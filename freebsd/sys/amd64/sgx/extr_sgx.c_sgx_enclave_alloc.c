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
struct sgx_softc {int dummy; } ;
struct sgx_enclave {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;
struct secs {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SGX ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct sgx_enclave* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sgx_enclave_alloc(struct sgx_softc *sc, struct secs *secs,
    struct sgx_enclave **enclave0)
{
	struct sgx_enclave *enclave;

	enclave = malloc(sizeof(struct sgx_enclave),
	    M_SGX, M_WAITOK | M_ZERO);

	enclave->base = secs->base;
	enclave->size = secs->size;

	*enclave0 = enclave;

	return (0);
}