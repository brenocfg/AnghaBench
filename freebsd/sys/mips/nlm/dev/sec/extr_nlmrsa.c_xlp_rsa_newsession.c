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
struct xlp_rsa_softc {int dummy; } ;
struct cryptoini {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  crypto_session_t ;

/* Variables and functions */
 int EINVAL ; 
 struct xlp_rsa_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xlp_rsa_newsession(device_t dev, crypto_session_t cses, struct cryptoini *cri)
{
	struct xlp_rsa_softc *sc = device_get_softc(dev);

	if (cri == NULL || sc == NULL)
		return (EINVAL);

	return (0);
}