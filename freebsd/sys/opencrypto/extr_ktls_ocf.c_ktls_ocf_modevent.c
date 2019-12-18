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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  counter_u64_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  counter_u64_free (int /*<<< orphan*/ ) ; 
 int ktls_crypto_backend_deregister (int /*<<< orphan*/ *) ; 
 int ktls_crypto_backend_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocf_backend ; 
 int /*<<< orphan*/  ocf_gcm_crypts ; 
 int /*<<< orphan*/  ocf_retries ; 

__attribute__((used)) static int
ktls_ocf_modevent(module_t mod, int what, void *arg)
{
	int error;

	switch (what) {
	case MOD_LOAD:
		ocf_gcm_crypts = counter_u64_alloc(M_WAITOK);
		ocf_retries = counter_u64_alloc(M_WAITOK);
		return (ktls_crypto_backend_register(&ocf_backend));
	case MOD_UNLOAD:
		error = ktls_crypto_backend_deregister(&ocf_backend);
		if (error)
			return (error);
		counter_u64_free(ocf_gcm_crypts);
		counter_u64_free(ocf_retries);
		return (0);
	default:
		return (EOPNOTSUPP);
	}
}