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
struct cbb_softc {int /*<<< orphan*/ * exca; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int cbb_do_power (int /*<<< orphan*/ ) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cbb_pcic_power_enable_socket(device_t brdev, device_t child)
{
	struct cbb_softc *sc = device_get_softc(brdev);
	int err;

	DPRINTF(("cbb_pcic_socket_enable:\n"));

	/* power down/up the socket to reset */
	err = cbb_do_power(brdev);
	if (err)
		return (err);
	exca_reset(&sc->exca[0], child);

	return (0);
}