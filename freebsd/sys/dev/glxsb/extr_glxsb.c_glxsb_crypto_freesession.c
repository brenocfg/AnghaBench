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
struct glxsb_softc {int dummy; } ;
struct glxsb_session {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  crypto_session_t ;

/* Variables and functions */
 struct glxsb_session* crypto_get_driver_session (int /*<<< orphan*/ ) ; 
 struct glxsb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glxsb_hash_free (struct glxsb_session*) ; 

__attribute__((used)) static void
glxsb_crypto_freesession(device_t dev, crypto_session_t cses)
{
	struct glxsb_softc *sc = device_get_softc(dev);
	struct glxsb_session *ses;

	if (sc == NULL)
		return;

	ses = crypto_get_driver_session(cses);
	glxsb_hash_free(ses);
}