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
struct envy24ht_spi_codec {scalar_t__ dir; size_t num; int /*<<< orphan*/  info; TYPE_1__* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** adc; int /*<<< orphan*/ ** dac; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ENVY24HT ; 
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spicds_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
envy24ht_spi_destroy(void *codec)
{
	struct envy24ht_spi_codec *ptr = codec;
	if (ptr == NULL)
		return;
#if(0)
	device_printf(ptr->parent->dev, "envy24ht_spi_destroy()\n");
#endif

	if (ptr->dir == PCMDIR_PLAY) {
		if (ptr->parent->dac[ptr->num] != NULL)
			spicds_destroy(ptr->info);
	}
	else {
		if (ptr->parent->adc[ptr->num] != NULL)
			spicds_destroy(ptr->info);
	}

	free(codec, M_ENVY24HT);
}