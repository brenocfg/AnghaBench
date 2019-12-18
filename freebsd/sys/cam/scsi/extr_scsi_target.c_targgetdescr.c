#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct targ_softc {int dummy; } ;
struct TYPE_2__ {scalar_t__ num_bufs_used; } ;
struct targ_cmd_descr {TYPE_1__ mapinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TARG ; 
 struct targ_cmd_descr* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct targ_cmd_descr *
targgetdescr(struct targ_softc *softc)
{
	struct targ_cmd_descr *descr;

	descr = malloc(sizeof(*descr), M_TARG,
	       M_NOWAIT);
	if (descr) {
		descr->mapinfo.num_bufs_used = 0;
	}
	return (descr);
}