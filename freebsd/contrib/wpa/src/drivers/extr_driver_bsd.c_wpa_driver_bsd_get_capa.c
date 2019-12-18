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
struct wpa_driver_capa {int dummy; } ;
struct bsd_driver_data {int /*<<< orphan*/  capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memcpy (struct wpa_driver_capa*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
wpa_driver_bsd_get_capa(void *priv, struct wpa_driver_capa *capa)
{
	struct bsd_driver_data *drv = priv;

	os_memcpy(capa, &drv->capa, sizeof(*capa));
	return 0;
}