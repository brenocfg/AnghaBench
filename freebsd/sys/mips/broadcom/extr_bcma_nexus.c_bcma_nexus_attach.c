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

/* Variables and functions */
 int bcma_attach (int /*<<< orphan*/ ) ; 
 int bhnd_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcma_nexus_attach(device_t dev)
{
	int error;

	/* Perform initial attach and enumerate our children. */
	if ((error = bcma_attach(dev)))
		goto failed;

	/* Delegate remainder to standard bhnd method implementation */
	if ((error = bhnd_generic_attach(dev)))
		goto failed;

	return (0);

failed:
	device_delete_children(dev);
	return (error);
}