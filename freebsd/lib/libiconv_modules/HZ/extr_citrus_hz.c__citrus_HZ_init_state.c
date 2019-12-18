#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  inuse; scalar_t__ chlen; } ;
typedef  TYPE_1__ _HZState ;
typedef  int /*<<< orphan*/  _HZEncodingInfo ;

/* Variables and functions */
 int /*<<< orphan*/  INIT0 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline void
_citrus_HZ_init_state(_HZEncodingInfo * __restrict ei,
    _HZState * __restrict psenc)
{

	psenc->chlen = 0;
	psenc->inuse = INIT0(ei);
}