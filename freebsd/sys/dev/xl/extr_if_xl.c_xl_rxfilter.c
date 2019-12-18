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
struct xl_softc {scalar_t__ xl_type; } ;

/* Variables and functions */
 scalar_t__ XL_TYPE_905B ; 
 int /*<<< orphan*/  xl_rxfilter_90x (struct xl_softc*) ; 
 int /*<<< orphan*/  xl_rxfilter_90xB (struct xl_softc*) ; 

__attribute__((used)) static void
xl_rxfilter(struct xl_softc *sc)
{

	if (sc->xl_type == XL_TYPE_905B)
		xl_rxfilter_90xB(sc);
	else
		xl_rxfilter_90x(sc);
}