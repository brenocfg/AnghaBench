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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bhnd_attach_type ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_ATTACH_NATIVE ; 

__attribute__((used)) static bhnd_attach_type
bhnd_nexus_get_attach_type(device_t dev, device_t child)
{
	return (BHND_ATTACH_NATIVE);
}