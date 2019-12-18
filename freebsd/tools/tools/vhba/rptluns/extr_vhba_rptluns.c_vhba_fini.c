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
struct TYPE_4__ {int /*<<< orphan*/  disk; } ;
typedef  TYPE_1__ vhbarptluns_t ;
struct TYPE_5__ {TYPE_1__* private; } ;
typedef  TYPE_2__ vhba_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vhba_fini(vhba_softc_t *vhba)
{
	vhbarptluns_t *vhbas = vhba->private;
	vhba->private = NULL;
	free(vhbas->disk, M_DEVBUF);
}