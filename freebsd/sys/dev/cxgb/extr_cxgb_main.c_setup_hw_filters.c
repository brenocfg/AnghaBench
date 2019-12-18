#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int nfilters; } ;
struct TYPE_5__ {TYPE_1__ mc5; } ;
struct adapter {TYPE_3__* filters; TYPE_2__ params; } ;
struct TYPE_6__ {scalar_t__ locked; } ;

/* Variables and functions */
 int set_filter (struct adapter*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  t3_enable_filters (struct adapter*) ; 

__attribute__((used)) static int
setup_hw_filters(struct adapter *sc)
{
	int i, rc;
	unsigned int nfilters = sc->params.mc5.nfilters;

	if (!sc->filters)
		return (0);

	t3_enable_filters(sc);

	for (i = rc = 0; i < nfilters && !rc; i++) {
		if (sc->filters[i].locked)
			rc = set_filter(sc, i, &sc->filters[i]);
	}

	return (rc);
}