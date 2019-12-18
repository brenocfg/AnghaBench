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
struct padlock_softc {int dummy; } ;
struct padlock_session {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  crypto_session_t ;

/* Variables and functions */
 struct padlock_session* crypto_get_driver_session (int /*<<< orphan*/ ) ; 
 struct padlock_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padlock_freesession_one (struct padlock_softc*,struct padlock_session*) ; 

__attribute__((used)) static void
padlock_freesession(device_t dev, crypto_session_t cses)
{
	struct padlock_softc *sc = device_get_softc(dev);
	struct padlock_session *ses;

	ses = crypto_get_driver_session(cses);
	padlock_freesession_one(sc, ses);
}