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
struct pxa_device_desc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pxa_device_desc pxa168_device_ssp1 ; 
 struct pxa_device_desc pxa168_device_ssp2 ; 
 struct pxa_device_desc pxa168_device_ssp3 ; 
 struct pxa_device_desc pxa168_device_ssp4 ; 
 struct pxa_device_desc pxa168_device_ssp5 ; 
 int pxa_register_device (struct pxa_device_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pxa168_add_ssp(int id)
{
	struct pxa_device_desc *d = NULL;

	switch (id) {
	case 1: d = &pxa168_device_ssp1; break;
	case 2: d = &pxa168_device_ssp2; break;
	case 3: d = &pxa168_device_ssp3; break;
	case 4: d = &pxa168_device_ssp4; break;
	case 5: d = &pxa168_device_ssp5; break;
	default:
		return -EINVAL;
	}
	return pxa_register_device(d, NULL, 0);
}