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
struct agp_i810_match {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  AGP_I852_GM 131 
#define  AGP_I852_GME 130 
#define  AGP_I855_GM 129 
#define  AGP_I855_GME 128 
 int /*<<< orphan*/  AGP_I85X_CAPID ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
agp_82852_set_desc(device_t dev, const struct agp_i810_match *match)
{

	switch (pci_read_config(dev, AGP_I85X_CAPID, 1)) {
	case AGP_I855_GME:
		device_set_desc(dev,
		    "Intel 82855GME (855GME GMCH) SVGA controller");
		break;
	case AGP_I855_GM:
		device_set_desc(dev,
		    "Intel 82855GM (855GM GMCH) SVGA controller");
		break;
	case AGP_I852_GME:
		device_set_desc(dev,
		    "Intel 82852GME (852GME GMCH) SVGA controller");
		break;
	case AGP_I852_GM:
		device_set_desc(dev,
		    "Intel 82852GM (852GM GMCH) SVGA controller");
		break;
	default:
		device_set_desc(dev,
		    "Intel 8285xM (85xGM GMCH) SVGA controller");
		break;
	}
}