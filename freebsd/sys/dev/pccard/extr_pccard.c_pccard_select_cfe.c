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
struct pccard_ivar {struct pccard_function* pf; } ;
struct pccard_function {scalar_t__ cfe; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct pccard_ivar* PCCARD_IVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pccard_function_init (struct pccard_function*,int) ; 

int
pccard_select_cfe(device_t dev, int entry)
{
	struct pccard_ivar *devi = PCCARD_IVAR(dev);
	struct pccard_function *pf = devi->pf;
	
	pccard_function_init(pf, entry);
	return (pf->cfe ? 0 : ENOMEM);
}