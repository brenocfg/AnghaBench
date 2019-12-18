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
struct sc_info {int /*<<< orphan*/ ** dac; int /*<<< orphan*/ ** adc; int /*<<< orphan*/  dev; } ;
struct envy24ht_spi_codec {int dir; int num; struct sc_info* parent; int /*<<< orphan*/ * info; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_ENVY24HT ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int PCMDIR_PLAY ; 
 int PCMDIR_REC ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  envy24ht_spi_ctl ; 
 int /*<<< orphan*/  free (struct envy24ht_spi_codec*,int /*<<< orphan*/ ) ; 
 struct envy24ht_spi_codec* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spicds_create (int /*<<< orphan*/ ,struct envy24ht_spi_codec*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
envy24ht_spi_create(device_t dev, void *info, int dir, int num)
{
	struct sc_info *sc = info;
	struct envy24ht_spi_codec *buff = NULL;

#if(0)
	device_printf(sc->dev, "envy24ht_spi_create(dev, sc, %d, %d)\n", dir, num);
#endif
	
	buff = malloc(sizeof(*buff), M_ENVY24HT, M_NOWAIT);
	if (buff == NULL)
		return NULL;

	if (dir == PCMDIR_REC && sc->adc[num] != NULL)
		buff->info = ((struct envy24ht_spi_codec *)sc->adc[num])->info;
	else if (dir == PCMDIR_PLAY && sc->dac[num] != NULL)
		buff->info = ((struct envy24ht_spi_codec *)sc->dac[num])->info;
	else
		buff->info = spicds_create(dev, buff, num, envy24ht_spi_ctl);
	if (buff->info == NULL) {
		free(buff, M_ENVY24HT);
		return NULL;
	}

	buff->parent = sc;
	buff->dir = dir;
	buff->num = num;

	return (void *)buff;
}