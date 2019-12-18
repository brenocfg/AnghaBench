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
struct hdacc_softc {int /*<<< orphan*/  fgs; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_HDACC ; 
 int device_delete_children (int /*<<< orphan*/ ) ; 
 struct hdacc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hdacc_detach(device_t dev)
{
	struct hdacc_softc *codec = device_get_softc(dev);
	int error;

	error = device_delete_children(dev);
	free(codec->fgs, M_HDACC);
	return (error);
}