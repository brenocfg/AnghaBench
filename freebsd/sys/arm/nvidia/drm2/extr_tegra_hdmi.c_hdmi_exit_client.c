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
struct tegra_drm {int dummy; } ;
struct hdmi_softc {int /*<<< orphan*/  output; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct hdmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_drm_encoder_exit (int /*<<< orphan*/ *,struct tegra_drm*) ; 

__attribute__((used)) static int
hdmi_exit_client(device_t dev, device_t host1x, struct tegra_drm *drm)
{
	struct hdmi_softc *sc;

	sc = device_get_softc(dev);
	tegra_drm_encoder_exit(&sc->output, drm);
	return (0);
}