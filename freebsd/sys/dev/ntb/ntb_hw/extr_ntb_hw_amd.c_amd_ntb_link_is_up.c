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
struct amd_ntb_softc {int dummy; } ;
typedef  enum ntb_width { ____Placeholder_ntb_width } ntb_width ;
typedef  enum ntb_speed { ____Placeholder_ntb_speed } ntb_speed ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int amd_link_is_up (struct amd_ntb_softc*) ; 
 int amd_ntb_link_sta_speed (struct amd_ntb_softc*) ; 
 int amd_ntb_link_sta_width (struct amd_ntb_softc*) ; 
 struct amd_ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
amd_ntb_link_is_up(device_t dev, enum ntb_speed *speed, enum ntb_width *width)
{
	struct amd_ntb_softc *ntb = device_get_softc(dev);

	if (speed != NULL)
		*speed = amd_ntb_link_sta_speed(ntb);
	if (width != NULL)
		*width = amd_ntb_link_sta_width(ntb);

	return (amd_link_is_up(ntb));
}