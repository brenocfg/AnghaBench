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
struct ess_info {int dummy; } ;
struct ess_chinfo {int stopping; int hwch; struct ess_info* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int ess_getmixer (struct ess_info*,int) ; 
 int ess_read (struct ess_info*,int) ; 
 int /*<<< orphan*/  ess_setmixer (struct ess_info*,int,int) ; 
 int /*<<< orphan*/  ess_write (struct ess_info*,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
ess_stop(struct ess_chinfo *ch)
{
	struct ess_info *sc = ch->parent;

	DEB(printf("ess_stop\n"));
	ch->stopping = 1;
	if (ch->hwch == 1)
		ess_write(sc, 0xb8, ess_read(sc, 0xb8) & ~0x04);
	else
		ess_setmixer(sc, 0x78, ess_getmixer(sc, 0x78) & ~0x10);
	DEB(printf("done with stop\n"));
	return 0;
}