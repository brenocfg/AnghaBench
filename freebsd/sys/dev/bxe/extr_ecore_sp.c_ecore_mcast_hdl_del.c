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
struct ecore_mcast_ramrod_params {int mcast_list_len; } ;
struct ecore_mcast_obj {int /*<<< orphan*/  (* set_one_rule ) (struct bxe_softc*,struct ecore_mcast_obj*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_MCAST_CMD_DEL ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct bxe_softc*,struct ecore_mcast_obj*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ecore_mcast_hdl_del(struct bxe_softc *sc,
	struct ecore_mcast_obj *o, struct ecore_mcast_ramrod_params *p,
	int *line_idx)
{
	int cnt = *line_idx, i;

	for (i = 0; i < p->mcast_list_len; i++) {
		o->set_one_rule(sc, o, cnt, NULL, ECORE_MCAST_CMD_DEL);

		cnt++;

		ECORE_MSG(sc, "Deleting MAC. %d left\n",
			  p->mcast_list_len - i - 1);
	}

	*line_idx = cnt;
}