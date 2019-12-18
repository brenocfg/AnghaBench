#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  t_softc; TYPE_1__* t_funcs; } ;
typedef  TYPE_2__ teken_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* tf_respond ) (int /*<<< orphan*/ ,void const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  teken_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
teken_funcs_respond(const teken_t *t, const void *buf, size_t len)
{

	teken_assert(t->t_funcs->tf_respond != NULL);
	t->t_funcs->tf_respond(t->t_softc, buf, len);
}