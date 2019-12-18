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
typedef  int /*<<< orphan*/  u32 ;
struct receive_sc {int /*<<< orphan*/  sci; } ;
struct macsec_qca_data {int /*<<< orphan*/  receive_channel_map; } ;

/* Variables and functions */
 int macsec_qca_lookup_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int macsec_qca_lookup_receive_channel(struct macsec_qca_data *drv,
					     struct receive_sc *sc,
					     u32 *channel)
{
	return macsec_qca_lookup_channel(drv->receive_channel_map, &sc->sci,
					 channel);
}