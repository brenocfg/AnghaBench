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
struct resource {int dummy; } ;
struct exca_softc {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int exca_io_findmap (struct exca_softc*,struct resource*) ; 
 int /*<<< orphan*/  exca_io_unmap (struct exca_softc*,int) ; 

int
exca_io_unmap_res(struct exca_softc *sc, struct resource *res)
{
	int win;

	win = exca_io_findmap(sc, res);
	if (win < 0)
		return (ENOENT);
	exca_io_unmap(sc, win);
	return (0);
}