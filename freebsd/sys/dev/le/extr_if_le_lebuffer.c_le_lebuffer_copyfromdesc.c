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
 int /*<<< orphan*/  be16enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_read_1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_read_2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_read_8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
le_lebuffer_copyfromdesc(struct lance_softc *sc, void *tov, int off, int len)
{
	struct le_lebuffer_softc *lesc = (struct le_lebuffer_softc *)sc;
	caddr_t to = tov;

	for (; len >= 8; len -= 8, off += 8, to += 8)
		be64enc(to,
		    bus_read_8(lesc->sc_bres, off));
	for (; len >= 4; len -= 4, off += 4, to += 4)
		be32enc(to,
		    bus_read_4(lesc->sc_bres, off));
	for (; len >= 2; len -= 2, off += 2, to += 2)
		be16enc(to,
		    bus_read_2(lesc->sc_bres, off));
	if (len == 1)
		*to = bus_read_1(lesc->sc_bres, off);
}