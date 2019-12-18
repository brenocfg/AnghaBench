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
struct sgx_softc {int /*<<< orphan*/  mtx_encls; } ;
struct epc_page {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sgx_eremove (void*) ; 

__attribute__((used)) static void
sgx_epc_page_remove(struct sgx_softc *sc,
    struct epc_page *epc)
{

	mtx_lock(&sc->mtx_encls);
	sgx_eremove((void *)epc->base);
	mtx_unlock(&sc->mtx_encls);
}