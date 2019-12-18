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
struct mii_data {int dummy; } ;
struct adm6996fc_softc {int numports; int cpuport; int /*<<< orphan*/ ** miibus; } ;

/* Variables and functions */
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mii_data *
adm6996fc_miiforport(struct adm6996fc_softc *sc, int port)
{

	if (port < 0 || port > sc->numports)
		return (NULL);
	if (port == sc->cpuport)
		return (NULL);
	return (device_get_softc(*sc->miibus[port]));
}