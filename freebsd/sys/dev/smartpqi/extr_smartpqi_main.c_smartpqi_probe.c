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
struct pqi_ident {int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_VENDOR ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pqi_ident* pqi_find_ident (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smartpqi_probe(device_t dev)
{
	struct pqi_ident *id;

	if ((id = pqi_find_ident(dev)) != NULL) {
		device_set_desc(dev, id->desc);	
		return(BUS_PROBE_VENDOR);
	}

	return(ENXIO);
}