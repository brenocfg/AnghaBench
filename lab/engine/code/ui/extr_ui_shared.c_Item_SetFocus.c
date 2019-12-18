#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ sfxHandle_t ;
struct TYPE_15__ {scalar_t__ h; int /*<<< orphan*/  y; } ;
typedef  TYPE_3__ rectDef_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_16__ {int itemCount; int cursorItem; TYPE_5__** items; } ;
typedef  TYPE_4__ menuDef_t ;
struct TYPE_14__ {int flags; } ;
struct TYPE_17__ {int cvarFlags; scalar_t__ type; scalar_t__ focusSound; scalar_t__ onFocus; TYPE_2__ window; TYPE_3__ textRect; scalar_t__ parent; } ;
typedef  TYPE_5__ itemDef_t ;
struct TYPE_13__ {scalar_t__ itemFocusSound; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* startLocalSound ) (scalar_t__,int /*<<< orphan*/ ) ;TYPE_1__ Assets; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_LOCAL_SOUND ; 
 int CVAR_DISABLE ; 
 int CVAR_ENABLE ; 
 int CVAR_HIDE ; 
 int CVAR_SHOW ; 
 TYPE_11__* DC ; 
 scalar_t__ ITEM_TYPE_TEXT ; 
 int /*<<< orphan*/  Item_EnableShowViaCvar (TYPE_5__*,int) ; 
 int /*<<< orphan*/  Item_RunScript (TYPE_5__*,scalar_t__) ; 
 TYPE_5__* Menu_ClearFocus (scalar_t__) ; 
 scalar_t__ Rect_ContainsPoint (TYPE_3__*,float,float) ; 
 int WINDOW_DECORATION ; 
 int WINDOW_HASFOCUS ; 
 int WINDOW_VISIBLE ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 

qboolean Item_SetFocus(itemDef_t *item, float x, float y) {
	int i;
	itemDef_t *oldFocus;
	sfxHandle_t *sfx = &DC->Assets.itemFocusSound;
	qboolean playSound = qfalse;
	menuDef_t *parent;
	// sanity check, non-null, not a decoration and does not already have the focus
	if (item == NULL || item->window.flags & WINDOW_DECORATION || item->window.flags & WINDOW_HASFOCUS || !(item->window.flags & WINDOW_VISIBLE)) {
		return qfalse;
	}

	// this can be NULL
	parent = (menuDef_t*)item->parent; 
      
	// items can be enabled and disabled based on cvars
	if (item->cvarFlags & (CVAR_ENABLE | CVAR_DISABLE) && !Item_EnableShowViaCvar(item, CVAR_ENABLE)) {
		return qfalse;
	}

	if (item->cvarFlags & (CVAR_SHOW | CVAR_HIDE) && !Item_EnableShowViaCvar(item, CVAR_SHOW)) {
		return qfalse;
	}

	oldFocus = Menu_ClearFocus(item->parent);

	if (item->type == ITEM_TYPE_TEXT) {
		rectDef_t r;
		r = item->textRect;
		r.y -= r.h;
		if (Rect_ContainsPoint(&r, x, y)) {
			item->window.flags |= WINDOW_HASFOCUS;
			if (item->focusSound) {
				sfx = &item->focusSound;
			}
			playSound = qtrue;
		} else {
			if (oldFocus) {
				oldFocus->window.flags |= WINDOW_HASFOCUS;
				if (oldFocus->onFocus) {
					Item_RunScript(oldFocus, oldFocus->onFocus);
				}
			}
		}
	} else {
	    item->window.flags |= WINDOW_HASFOCUS;
		if (item->onFocus) {
			Item_RunScript(item, item->onFocus);
		}
		if (item->focusSound) {
			sfx = &item->focusSound;
		}
		playSound = qtrue;
	}

	if (playSound && sfx) {
		DC->startLocalSound( *sfx, CHAN_LOCAL_SOUND );
	}

	for (i = 0; i < parent->itemCount; i++) {
		if (parent->items[i] == item) {
			parent->cursorItem = i;
			break;
		}
	}

	return qtrue;
}