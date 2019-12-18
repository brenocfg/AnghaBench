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
struct wpa_driver_privsep_data {int dummy; } ;
struct wpa_driver_capa {scalar_t__ extended_capa_len; int /*<<< orphan*/ * extended_capa_mask; int /*<<< orphan*/ * extended_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIVSEP_CMD_GET_CAPA ; 
 int wpa_priv_cmd (struct wpa_driver_privsep_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wpa_driver_capa*,size_t*) ; 

__attribute__((used)) static int wpa_driver_privsep_get_capa(void *priv,
				       struct wpa_driver_capa *capa)
{
	struct wpa_driver_privsep_data *drv = priv;
	int res;
	size_t len = sizeof(*capa);

	res = wpa_priv_cmd(drv, PRIVSEP_CMD_GET_CAPA, NULL, 0, capa, &len);
	if (res < 0 || len != sizeof(*capa))
		return -1;
	/* For now, no support for passing extended_capa pointers */
	capa->extended_capa = NULL;
	capa->extended_capa_mask = NULL;
	capa->extended_capa_len = 0;
	return 0;
}