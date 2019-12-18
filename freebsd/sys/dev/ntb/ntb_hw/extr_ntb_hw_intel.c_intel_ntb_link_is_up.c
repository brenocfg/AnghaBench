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
struct ntb_softc {int dummy; } ;
typedef  enum ntb_width { ____Placeholder_ntb_width } ntb_width ;
typedef  enum ntb_speed { ____Placeholder_ntb_speed } ntb_speed ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int intel_ntb_link_sta_speed (struct ntb_softc*) ; 
 int intel_ntb_link_sta_width (struct ntb_softc*) ; 
 int link_is_up (struct ntb_softc*) ; 

__attribute__((used)) static bool
intel_ntb_link_is_up(device_t dev, enum ntb_speed *speed, enum ntb_width *width)
{
	struct ntb_softc *ntb = device_get_softc(dev);

	if (speed != NULL)
		*speed = intel_ntb_link_sta_speed(ntb);
	if (width != NULL)
		*width = intel_ntb_link_sta_width(ntb);
	return (link_is_up(ntb));
}