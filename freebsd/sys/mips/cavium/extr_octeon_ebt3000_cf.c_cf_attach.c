#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cf_priv {int /*<<< orphan*/  cf_bq; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ board_type; } ;

/* Variables and functions */
 scalar_t__ CVMX_BOARD_TYPE_SIM ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_attach_geom ; 
 int cf_cmd_identify (struct cf_priv*) ; 
 TYPE_1__* cvmx_sysinfo_get () ; 
 struct cf_priv* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_post_event (int /*<<< orphan*/ ,struct cf_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cf_attach (device_t dev)
{
	struct cf_priv *cf_priv;
	int error;

    	if (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_SIM)
		return (ENXIO);

	cf_priv = device_get_softc(dev);
	cf_priv->dev = dev;

	error = cf_cmd_identify(cf_priv);
	if (error != 0) {
		device_printf(dev, "cf_cmd_identify failed: %d\n", error);
		return (error);
	}

	g_post_event(cf_attach_geom, cf_priv, M_WAITOK, NULL);
	bioq_init(&cf_priv->cf_bq);

        return 0;
}