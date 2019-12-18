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
struct aesni_softc {int /*<<< orphan*/  cid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  aesni_cleanctx () ; 
 int /*<<< orphan*/  crypto_unregister_all (int /*<<< orphan*/ ) ; 
 struct aesni_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aesni_detach(device_t dev)
{
	struct aesni_softc *sc;

	sc = device_get_softc(dev);

	crypto_unregister_all(sc->cid);

	aesni_cleanctx();

	return (0);
}