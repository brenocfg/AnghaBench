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
struct uath_softc {int dummy; } ;
struct uath_cmd {int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int UATH_CMD_LIST_COUNT ; 

__attribute__((used)) static void
uath_free_cmd_list(struct uath_softc *sc, struct uath_cmd cmds[])
{
	int i;

	for (i = 0; i != UATH_CMD_LIST_COUNT; i++)
		cmds[i].buf = NULL;
}