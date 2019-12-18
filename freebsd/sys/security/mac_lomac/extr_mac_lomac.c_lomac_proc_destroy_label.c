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
struct label {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_LOMAC ; 
 TYPE_1__* PSLOT (struct label*) ; 
 int /*<<< orphan*/  PSLOT_SET (struct label*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lomac_proc_destroy_label(struct label *label)
{

	mtx_destroy(&PSLOT(label)->mtx);
	free(PSLOT(label), M_LOMAC);
	PSLOT_SET(label, NULL);
}