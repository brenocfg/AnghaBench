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
struct macsec_init_params {int dummy; } ;

/* Variables and functions */
 int wpa_drv_macsec_init (void*,struct macsec_init_params*) ; 

__attribute__((used)) static int wpas_macsec_init(void *priv, struct macsec_init_params *params)
{
	return wpa_drv_macsec_init(priv, params);
}