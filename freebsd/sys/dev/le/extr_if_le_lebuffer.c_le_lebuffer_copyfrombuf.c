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
 int /*<<< orphan*/  bus_read_1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_read_2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le16enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
le_lebuffer_copyfrombuf(struct lance_softc *sc, void *tov, int off, int len)
{
	struct le_lebuffer_softc *lesc = (struct le_lebuffer_softc *)sc;
	caddr_t to = tov;

	for (; len >= 2; len -= 2, off += 2, to += 2)
		le16enc(to,
		    bus_read_2(lesc->sc_bres, off));
	if (len == 1)
		*to = bus_read_1(lesc->sc_bres, off + 1);
}