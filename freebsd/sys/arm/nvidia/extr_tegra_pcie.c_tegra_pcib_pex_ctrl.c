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
struct tegra_pcib_softc {int dummy; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  AFI_PEX0_CTRL ; 
 int /*<<< orphan*/  AFI_PEX1_CTRL ; 
 int /*<<< orphan*/  AFI_PEX2_CTRL ; 
 int TEGRA_PCIB_MAX_PORTS ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static bus_size_t
tegra_pcib_pex_ctrl(struct tegra_pcib_softc *sc, int port)
{
	if (port >= TEGRA_PCIB_MAX_PORTS)
		panic("invalid port number: %d\n", port);

	if (port == 0)
		return (AFI_PEX0_CTRL);
	else if (port == 1)
		return (AFI_PEX1_CTRL);
	else if (port == 2)
		return (AFI_PEX2_CTRL);
	else
		panic("invalid port number: %d\n", port);
}