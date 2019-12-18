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
struct sdhci_pxa_platdata {int dummy; } ;
struct pxa_device_desc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pxa_device_desc mmp2_device_sdh0 ; 
 struct pxa_device_desc mmp2_device_sdh1 ; 
 struct pxa_device_desc mmp2_device_sdh2 ; 
 struct pxa_device_desc mmp2_device_sdh3 ; 
 int pxa_register_device (struct pxa_device_desc*,struct sdhci_pxa_platdata*,int) ; 

__attribute__((used)) static inline int mmp2_add_sdhost(int id, struct sdhci_pxa_platdata *data)
{
	struct pxa_device_desc *d = NULL;

	switch (id) {
	case 0: d = &mmp2_device_sdh0; break;
	case 1: d = &mmp2_device_sdh1; break;
	case 2: d = &mmp2_device_sdh2; break;
	case 3: d = &mmp2_device_sdh3; break;
	default:
		return -EINVAL;
	}

	return pxa_register_device(d, data, sizeof(*data));
}