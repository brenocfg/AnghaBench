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
struct ismt_softc {scalar_t__ bus_reserved; scalar_t__ head; struct ismt_desc* desc; } ;
struct ismt_desc {int dummy; } ;

/* Variables and functions */
 scalar_t__ ISMT_DESC_ENTRIES ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ curthread ; 
 int /*<<< orphan*/  memset (struct ismt_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ismt_desc *
ismt_alloc_desc(struct ismt_softc *sc)
{
	struct ismt_desc *desc;

	KASSERT(sc->bus_reserved == curthread,
	    ("curthread %p did not request bus (%p has reserved)\n",
	    curthread, sc->bus_reserved));

	desc = &sc->desc[sc->head++];
	if (sc->head == ISMT_DESC_ENTRIES)
		sc->head = 0;

	memset(desc, 0, sizeof(*desc));

	return (desc);
}