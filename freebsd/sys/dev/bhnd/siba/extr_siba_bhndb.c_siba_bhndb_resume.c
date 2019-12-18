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
struct siba_bhndb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct siba_bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int siba_bhndb_wars_hwup (struct siba_bhndb_softc*) ; 
 int siba_resume (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
siba_bhndb_resume(device_t dev)
{
	struct siba_bhndb_softc	*sc;
	int			 error;

	sc = device_get_softc(dev);

	/* Apply attach/resume work-arounds */
	if ((error = siba_bhndb_wars_hwup(sc)))
		return (error);

	/* Call our superclass' implementation */
	return (siba_resume(dev));
}