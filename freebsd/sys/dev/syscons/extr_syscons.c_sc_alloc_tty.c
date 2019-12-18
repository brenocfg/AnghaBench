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
struct tty {int dummy; } ;
struct sc_ttysoftc {int st_index; int /*<<< orphan*/ * st_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct sc_ttysoftc* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_ttydevsw ; 
 struct tty* tty_alloc_mutex (int /*<<< orphan*/ *,struct sc_ttysoftc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_makedev (struct tty*,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static struct tty *
sc_alloc_tty(int index, int devnum)
{
	struct sc_ttysoftc *stc;
	struct tty *tp;

	/* Allocate TTY object and softc to store unit number. */
	stc = malloc(sizeof(struct sc_ttysoftc), M_DEVBUF, M_WAITOK);
	stc->st_index = index;
	stc->st_stat = NULL;
	tp = tty_alloc_mutex(&sc_ttydevsw, stc, &Giant);

	/* Create device node. */
	tty_makedev(tp, NULL, "v%r", devnum);

	return (tp);
}