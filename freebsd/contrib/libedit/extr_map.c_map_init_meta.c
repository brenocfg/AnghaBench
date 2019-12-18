#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
typedef  scalar_t__ el_action_t ;
struct TYPE_6__ {scalar_t__ type; scalar_t__* alt; scalar_t__* key; } ;
struct TYPE_7__ {TYPE_1__ el_map; } ;
typedef  TYPE_2__ EditLine ;

/* Variables and functions */
#define  ED_INSERT 130 
#define  ED_SEQUENCE_LEAD_IN 129 
#define  ED_UNASSIGNED 128 
 scalar_t__ EM_META_NEXT ; 
 scalar_t__ MAP_VI ; 
 int /*<<< orphan*/  XK_CMD ; 
 int /*<<< orphan*/  keymacro_add (TYPE_2__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keymacro_map_cmd (TYPE_2__*,int) ; 

__attribute__((used)) static void
map_init_meta(EditLine *el)
{
	wchar_t buf[3];
	int i;
	el_action_t *map = el->el_map.key;
	el_action_t *alt = el->el_map.alt;

	for (i = 0; i <= 0377 && map[i] != EM_META_NEXT; i++)
		continue;

	if (i > 0377) {
		for (i = 0; i <= 0377 && alt[i] != EM_META_NEXT; i++)
			continue;
		if (i > 0377) {
			i = 033;
			if (el->el_map.type == MAP_VI)
				map = alt;
		} else
			map = alt;
	}
	buf[0] = (wchar_t)i;
	buf[2] = 0;
	for (i = 0200; i <= 0377; i++)
		switch (map[i]) {
		case ED_INSERT:
		case ED_UNASSIGNED:
		case ED_SEQUENCE_LEAD_IN:
			break;
		default:
			buf[1] = i & 0177;
			keymacro_add(el, buf, keymacro_map_cmd(el, (int) map[i]), XK_CMD);
			break;
		}
	map[(int) buf[0]] = ED_SEQUENCE_LEAD_IN;
}