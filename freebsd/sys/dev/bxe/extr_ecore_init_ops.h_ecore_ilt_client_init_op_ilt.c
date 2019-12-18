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
typedef  int /*<<< orphan*/  uint8_t ;
struct ilt_client_info {int flags; int start; int end; } ;
struct ecore_ilt {int /*<<< orphan*/  start_line; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int ILT_CLIENT_SKIP_INIT ; 
 int /*<<< orphan*/  ecore_ilt_boundry_init_op (struct bxe_softc*,struct ilt_client_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_ilt_line_init_op (struct bxe_softc*,struct ecore_ilt*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_ilt_client_init_op_ilt(struct bxe_softc *sc,
					 struct ecore_ilt *ilt,
					 struct ilt_client_info *ilt_cli,
					 uint8_t initop)
{
	int i;

	if (ilt_cli->flags & ILT_CLIENT_SKIP_INIT)
		return;

	for (i = ilt_cli->start; i <= ilt_cli->end; i++)
		ecore_ilt_line_init_op(sc, ilt, i, initop);

	/* init/clear the ILT boundries */
	ecore_ilt_boundry_init_op(sc, ilt_cli, ilt->start_line, initop);
}