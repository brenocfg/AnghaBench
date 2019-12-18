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
struct chipc_caps {int /*<<< orphan*/  sprom_offset; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_CHIPC_DISABLE_SPROM (int /*<<< orphan*/ ) ; 
 int BHND_CHIPC_ENABLE_SPROM (int /*<<< orphan*/ ) ; 
 struct chipc_caps* BHND_CHIPC_GET_CAPS (int /*<<< orphan*/ ) ; 
 int bhnd_sprom_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chipc_sprom_attach(device_t dev)
{
	struct chipc_caps	*caps;
	device_t		 chipc;
	int			 error;

	chipc = device_get_parent(dev);
	caps = BHND_CHIPC_GET_CAPS(chipc);

	/* Request that ChipCommon enable access to SPROM hardware before
	 * delegating attachment (and SPROM parsing) to the common driver */
	if ((error = BHND_CHIPC_ENABLE_SPROM(chipc)))
		return (error);

	error = bhnd_sprom_attach(dev, caps->sprom_offset);
	BHND_CHIPC_DISABLE_SPROM(chipc);
	return (error);
}