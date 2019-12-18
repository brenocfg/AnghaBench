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
struct chipc_caps {int /*<<< orphan*/  nvram_src; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct chipc_caps* BHND_CHIPC_GET_CAPS (int /*<<< orphan*/ ) ; 
 int BUS_PROBE_NOWILDCARD ; 
 int /*<<< orphan*/  CHIPC_VALID_SPROM_SRC (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int bhnd_sprom_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chipc_sprom_probe(device_t dev)
{
	struct chipc_caps	*caps;
	device_t		 chipc;
	int			 error;

	chipc = device_get_parent(dev);
	caps = BHND_CHIPC_GET_CAPS(chipc);

	/* Only match on SPROM/OTP devices */
	if (!CHIPC_VALID_SPROM_SRC(caps->nvram_src))
		return (ENXIO);

	/* Defer to default driver implementation */
	if ((error = bhnd_sprom_probe(dev)) > 0)
		return (error);

	return (BUS_PROBE_NOWILDCARD);
}