#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct envy24_delta_ak4524_codec {int cs; int num; TYPE_2__* parent; int /*<<< orphan*/  info; int /*<<< orphan*/  cdti; int /*<<< orphan*/  cclk; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; TYPE_1__* cfg; } ;
struct TYPE_4__ {int cs; int subvendor; int subdevice; int /*<<< orphan*/  cif; int /*<<< orphan*/  type; int /*<<< orphan*/  cdti; int /*<<< orphan*/  cclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK452X_DVC_DEMOFF ; 
 int AK452X_FORMAT_1X ; 
 int AK452X_FORMAT_256FSN ; 
 int AK452X_FORMAT_I2S ; 
 int /*<<< orphan*/  ENVY24_GPIO_AK4524_CCLK ; 
 int ENVY24_GPIO_AK4524_CS0 ; 
 int ENVY24_GPIO_AK4524_CS1 ; 
 int /*<<< orphan*/  ENVY24_GPIO_CS8414_STATUS ; 
 int /*<<< orphan*/  PCA9554_DIR ; 
 int /*<<< orphan*/  PCA9554_I2CDEV ; 
 int /*<<< orphan*/  PCA9554_OUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  envy24_gpio_i2c_ctl ; 
 int /*<<< orphan*/  envy24_gpiosetdir (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  envy24_gpiosetmask (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_wr (struct envy24_delta_ak4524_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spicds_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spicds_setcif (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spicds_setdvc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spicds_setformat (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spicds_settype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
envy24_delta_ak4524_init(void *codec)
{
#if 0
	u_int32_t gpiomask, gpiodir;
#endif
	struct envy24_delta_ak4524_codec *ptr = codec;
	if (ptr == NULL)
		return;
#if(0)
	device_printf(ptr->parent->dev, "envy24_delta_ak4524_init()\n");
#endif

	/*
	gpiomask = envy24_gpiogetmask(ptr->parent);
	gpiomask &= ~(ENVY24_GPIO_AK4524_CDTI | ENVY24_GPIO_AK4524_CCLK | ENVY24_GPIO_AK4524_CS0 | ENVY24_GPIO_AK4524_CS1);
	envy24_gpiosetmask(ptr->parent, gpiomask);
	gpiodir = envy24_gpiogetdir(ptr->parent);
	gpiodir |= ENVY24_GPIO_AK4524_CDTI | ENVY24_GPIO_AK4524_CCLK | ENVY24_GPIO_AK4524_CS0 | ENVY24_GPIO_AK4524_CS1;
	envy24_gpiosetdir(ptr->parent, gpiodir);
	*/
	ptr->cs = ptr->parent->cfg->cs;
#if 0
	envy24_gpiosetmask(ptr->parent, ENVY24_GPIO_CS8414_STATUS);
	envy24_gpiosetdir(ptr->parent, ~ENVY24_GPIO_CS8414_STATUS);
	if (ptr->num == 0)
		ptr->cs = ENVY24_GPIO_AK4524_CS0;
	else
		ptr->cs = ENVY24_GPIO_AK4524_CS1;
	ptr->cclk = ENVY24_GPIO_AK4524_CCLK;
#endif
	ptr->cclk = ptr->parent->cfg->cclk;
	ptr->cdti = ptr->parent->cfg->cdti;
	spicds_settype(ptr->info,  ptr->parent->cfg->type);
	spicds_setcif(ptr->info, ptr->parent->cfg->cif);
	spicds_setformat(ptr->info,
	    AK452X_FORMAT_I2S | AK452X_FORMAT_256FSN | AK452X_FORMAT_1X);
	spicds_setdvc(ptr->info, AK452X_DVC_DEMOFF);
	/* for the time being, init only first codec */
	if (ptr->num == 0)
		spicds_init(ptr->info);

        /* 6fire rear input init test, set ptr->num to 1 for test */
        if (ptr->parent->cfg->subvendor == 0x153b && \
                ptr->parent->cfg->subdevice == 0x1138 && ptr->num == 100) {
                ptr->cs = 0x02;  
                spicds_init(ptr->info);
                device_printf(ptr->parent->dev, "6fire rear input init\n");
                i2c_wr(ptr, envy24_gpio_i2c_ctl, \
                        PCA9554_I2CDEV, PCA9554_DIR, 0x80);
                i2c_wr(ptr, envy24_gpio_i2c_ctl, \
                        PCA9554_I2CDEV, PCA9554_OUT, 0x02);
        }
}