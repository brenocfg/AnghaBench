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
struct sc_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ds_init (struct sc_info*) ; 
 int mixer_reinit (int /*<<< orphan*/ ) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ds_pci_resume(device_t dev)
{
       struct sc_info *sc;

       sc = pcm_getdevinfo(dev);

       if (ds_init(sc) == -1) {
           device_printf(dev, "unable to reinitialize the card\n");
           return ENXIO;
       }
       if (mixer_reinit(dev) == -1) {
               device_printf(dev, "unable to reinitialize the mixer\n");
               return ENXIO;
       }
       return 0;
}