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
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  menuDef_t ;
struct TYPE_4__ {int flags; } ;
struct TYPE_5__ {TYPE_1__ window; } ;
typedef  TYPE_2__ itemDef_t ;

/* Variables and functions */
 TYPE_2__* Menu_GetMatchingItemByNumber (int /*<<< orphan*/ *,int,char const*) ; 
 int Menu_ItemsMatchingGroup (int /*<<< orphan*/ *,char const*) ; 
 int WINDOW_FADINGIN ; 
 int WINDOW_FADINGOUT ; 
 int WINDOW_VISIBLE ; 

void Menu_FadeItemByName(menuDef_t *menu, const char *p, qboolean fadeOut) {
  itemDef_t *item;
  int i;
  int count = Menu_ItemsMatchingGroup(menu, p);
  for (i = 0; i < count; i++) {
    item = Menu_GetMatchingItemByNumber(menu, i, p);
    if (item != NULL) {
      if (fadeOut) {
        item->window.flags |= (WINDOW_FADINGOUT | WINDOW_VISIBLE);
        item->window.flags &= ~WINDOW_FADINGIN;
      } else {
        item->window.flags |= (WINDOW_VISIBLE | WINDOW_FADINGIN);
        item->window.flags &= ~WINDOW_FADINGOUT;
      }
    }
  }
}