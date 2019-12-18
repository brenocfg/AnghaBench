#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sector_size; int nr_sectors; } ;
struct cf_priv {TYPE_2__* cf_provider; TYPE_1__ drive_param; TYPE_3__* cf_geom; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; struct cf_priv* softc; } ;
struct TYPE_7__ {int sectorsize; int mediasize; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_cf_class ; 
 int /*<<< orphan*/  g_error_provider (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* g_new_geomf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* g_new_providerf (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cf_attach_geom (void *arg, int flag)
{
	struct cf_priv *cf_priv;

	cf_priv = (struct cf_priv *) arg;
	cf_priv->cf_geom = g_new_geomf(&g_cf_class, "cf%d", device_get_unit(cf_priv->dev));
	cf_priv->cf_geom->softc = cf_priv;
	cf_priv->cf_provider = g_new_providerf(cf_priv->cf_geom, "%s",
	    cf_priv->cf_geom->name);
	cf_priv->cf_provider->sectorsize = cf_priv->drive_param.sector_size;
	cf_priv->cf_provider->mediasize = cf_priv->drive_param.nr_sectors * cf_priv->cf_provider->sectorsize;
        g_error_provider(cf_priv->cf_provider, 0);
}