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
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mly_free (int /*<<< orphan*/ ) ; 
 int mly_shutdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mly_detach(device_t dev)
{
    int			error;

    if ((error = mly_shutdown(dev)) != 0)
	return(error);
    
    mly_free(device_get_softc(dev));
    return(0);
}