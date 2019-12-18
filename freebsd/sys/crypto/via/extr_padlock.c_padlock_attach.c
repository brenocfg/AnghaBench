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
struct padlock_softc {scalar_t__ sc_cid; } ;
struct padlock_session {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTOCAP_F_HARDWARE ; 
 int /*<<< orphan*/  CRYPTO_AES_CBC ; 
 int /*<<< orphan*/  CRYPTO_MD5_HMAC ; 
 int /*<<< orphan*/  CRYPTO_RIPEMD160_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA1_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA2_256_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA2_384_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA2_512_HMAC ; 
 int ENOMEM ; 
 scalar_t__ crypto_get_driverid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_register (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct padlock_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
padlock_attach(device_t dev)
{
	struct padlock_softc *sc = device_get_softc(dev);

	sc->sc_cid = crypto_get_driverid(dev, sizeof(struct padlock_session),
	    CRYPTOCAP_F_HARDWARE);
	if (sc->sc_cid < 0) {
		device_printf(dev, "Could not get crypto driver id.\n");
		return (ENOMEM);
	}

	crypto_register(sc->sc_cid, CRYPTO_AES_CBC, 0, 0);
	crypto_register(sc->sc_cid, CRYPTO_MD5_HMAC, 0, 0);
	crypto_register(sc->sc_cid, CRYPTO_SHA1_HMAC, 0, 0);
	crypto_register(sc->sc_cid, CRYPTO_RIPEMD160_HMAC, 0, 0);
	crypto_register(sc->sc_cid, CRYPTO_SHA2_256_HMAC, 0, 0);
	crypto_register(sc->sc_cid, CRYPTO_SHA2_384_HMAC, 0, 0);
	crypto_register(sc->sc_cid, CRYPTO_SHA2_512_HMAC, 0, 0);
	return (0);
}