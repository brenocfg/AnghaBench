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
struct drbg_state {int fips_primed; int /*<<< orphan*/ * prev; int /*<<< orphan*/ * core; int /*<<< orphan*/ * d_ops; scalar_t__ reseed_ctr; int /*<<< orphan*/ * scratchpadbuf; int /*<<< orphan*/ * C; int /*<<< orphan*/ * Cbuf; int /*<<< orphan*/ * V; int /*<<< orphan*/ * Vbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CRYPTO_FIPS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void drbg_dealloc_state(struct drbg_state *drbg)
{
	if (!drbg)
		return;
	kzfree(drbg->Vbuf);
	drbg->Vbuf = NULL;
	drbg->V = NULL;
	kzfree(drbg->Cbuf);
	drbg->Cbuf = NULL;
	drbg->C = NULL;
	kzfree(drbg->scratchpadbuf);
	drbg->scratchpadbuf = NULL;
	drbg->reseed_ctr = 0;
	drbg->d_ops = NULL;
	drbg->core = NULL;
	if (IS_ENABLED(CONFIG_CRYPTO_FIPS)) {
		kzfree(drbg->prev);
		drbg->prev = NULL;
		drbg->fips_primed = false;
	}
}