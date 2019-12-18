#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int gr; int singlegl; int singlegr; int /*<<< orphan*/  flags; TYPE_1__* g; scalar_t__ gl; } ;
typedef  TYPE_3__ _ISO2022State ;
struct TYPE_11__ {int flags; TYPE_2__* initg; } ;
typedef  TYPE_4__ _ISO2022EncodingInfo ;
struct TYPE_9__ {int /*<<< orphan*/  interm; scalar_t__ final; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/  interm; scalar_t__ final; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int F_8BIT ; 
 int /*<<< orphan*/  _ISO2022STATE_FLAG_INITIALIZED ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
/*ARGSUSED*/
_citrus_ISO2022_init_state(_ISO2022EncodingInfo * __restrict ei,
    _ISO2022State * __restrict s)
{
	int i;

	memset(s, 0, sizeof(*s));
	s->gl = 0;
	s->gr = (ei->flags & F_8BIT) ? 1 : -1;

	for (i = 0; i < 4; i++)
		if (ei->initg[i].final) {
			s->g[i].type = ei->initg[i].type;
			s->g[i].final = ei->initg[i].final;
			s->g[i].interm = ei->initg[i].interm;
		}
	s->singlegl = s->singlegr = -1;
	s->flags |= _ISO2022STATE_FLAG_INITIALIZED;
}