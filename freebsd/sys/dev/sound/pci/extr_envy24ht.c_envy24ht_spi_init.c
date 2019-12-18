#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct envy24ht_spi_codec {scalar_t__ num; int /*<<< orphan*/  info; TYPE_2__* parent; int /*<<< orphan*/  cdti; int /*<<< orphan*/  cclk; int /*<<< orphan*/  cs; } ;
struct TYPE_4__ {TYPE_1__* cfg; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  cif; int /*<<< orphan*/  cdti; int /*<<< orphan*/  cclk; int /*<<< orphan*/  cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK452X_DVC_DEMOFF ; 
 int AK452X_FORMAT_1X ; 
 int AK452X_FORMAT_256FSN ; 
 int AK452X_FORMAT_I2S ; 
 scalar_t__ SPICDS_TYPE_AK4524 ; 
 scalar_t__ SPICDS_TYPE_AK4528 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spicds_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spicds_setcif (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spicds_setdvc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spicds_setformat (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spicds_settype (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
envy24ht_spi_init(void *codec)
{
	struct envy24ht_spi_codec *ptr = codec;
	if (ptr == NULL)
		return;
#if(0)
	device_printf(ptr->parent->dev, "envy24ht_spicds_init()\n");
#endif
        ptr->cs = ptr->parent->cfg->cs;
	ptr->cclk = ptr->parent->cfg->cclk;
	ptr->cdti =  ptr->parent->cfg->cdti;
	spicds_settype(ptr->info, ptr->parent->cfg->type);
	spicds_setcif(ptr->info, ptr->parent->cfg->cif);
	if (ptr->parent->cfg->type == SPICDS_TYPE_AK4524 || \
	ptr->parent->cfg->type == SPICDS_TYPE_AK4528) {
	spicds_setformat(ptr->info,
	    AK452X_FORMAT_I2S | AK452X_FORMAT_256FSN | AK452X_FORMAT_1X);
	spicds_setdvc(ptr->info, AK452X_DVC_DEMOFF);
	}

	/* for the time being, init only first codec */
	if (ptr->num == 0)
	spicds_init(ptr->info);
}