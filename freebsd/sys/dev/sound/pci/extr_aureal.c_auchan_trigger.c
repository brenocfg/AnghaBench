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
struct au_info {int dummy; } ;
struct au_chinfo {scalar_t__ dir; struct au_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
 int PCMTRIG_START ; 
 int /*<<< orphan*/  au_delroute (struct au_info*,int) ; 
 int /*<<< orphan*/  au_setadb (struct au_info*,int,int) ; 
 int /*<<< orphan*/  au_wr (struct au_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
auchan_trigger(kobj_t obj, void *data, int go)
{
	struct au_chinfo *ch = data;
	struct au_info *au = ch->parent;

	if (!PCMTRIG_COMMON(go))
		return 0;

	if (ch->dir == PCMDIR_PLAY) {
		au_setadb(au, 0x11, (go)? 1 : 0);
		if (go != PCMTRIG_START) {
			au_wr(au, 0, 0xf800, 0, 4);
			au_wr(au, 0, 0xf804, 0, 4);
			au_delroute(au, 0x58);
			au_delroute(au, 0x59);
		}
	} else {
	}
	return 0;
}