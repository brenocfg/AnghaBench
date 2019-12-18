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
struct le_lebuffer_softc {int /*<<< orphan*/  sc_bres; } ;
struct lance_softc {int dummy; } ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  be16dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be32dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be64dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
le_lebuffer_copytodesc(struct lance_softc *sc, void *fromv, int off, int len)
{
	struct le_lebuffer_softc *lesc = (struct le_lebuffer_softc *)sc;
	caddr_t from = fromv;

	for (; len >= 8; len -= 8, off += 8, from += 8)
		bus_write_8(lesc->sc_bres, off, be64dec(from));
	for (; len >= 4; len -= 4, off += 4, from += 4)
		bus_write_4(lesc->sc_bres, off, be32dec(from));
	for (; len >= 2; len -= 2, off += 2, from += 2)
		bus_write_2(lesc->sc_bres, off, be16dec(from));
	if (len == 1)
		bus_write_1(lesc->sc_bres, off, *from);
}