#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_8__ {int cursorPos; scalar_t__ type; int /*<<< orphan*/  parent; scalar_t__ cvar; scalar_t__ typeData; } ;
typedef  TYPE_1__ itemDef_t ;
struct TYPE_9__ {int maxChars; int paintOffset; int maxPaintChars; } ;
typedef  TYPE_2__ editFieldDef_t ;
typedef  int /*<<< orphan*/  buff ;
struct TYPE_10__ {int /*<<< orphan*/  (* getOverstrikeMode ) () ;int /*<<< orphan*/  (* setOverstrikeMode ) (int) ;int /*<<< orphan*/  (* setCVar ) (scalar_t__,char*) ;int /*<<< orphan*/  (* getCVarString ) (scalar_t__,char*,int) ;} ;

/* Variables and functions */
 TYPE_7__* DC ; 
 scalar_t__ ITEM_TYPE_EDITFIELD ; 
 scalar_t__ ITEM_TYPE_NUMERICFIELD ; 
 int K_CHAR_FLAG ; 
 int K_DEL ; 
 int K_DOWNARROW ; 
 int K_END ; 
 int K_ENTER ; 
 int K_ESCAPE ; 
 int K_HOME ; 
 int K_INS ; 
 int K_KP_DEL ; 
 int K_KP_DOWNARROW ; 
 int K_KP_END ; 
 int K_KP_ENTER ; 
 int K_KP_HOME ; 
 int K_KP_INS ; 
 int K_KP_LEFTARROW ; 
 int K_KP_RIGHTARROW ; 
 int K_KP_UPARROW ; 
 int K_LEFTARROW ; 
 int K_RIGHTARROW ; 
 int K_TAB ; 
 int K_UPARROW ; 
 int MAX_EDITFIELD ; 
 TYPE_1__* Menu_SetNextCursorItem (int /*<<< orphan*/ ) ; 
 TYPE_1__* Menu_SetPrevCursorItem (int /*<<< orphan*/ ) ; 
 TYPE_1__* g_editItem ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,char*) ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  stub4 (scalar_t__,char*) ; 
 int /*<<< orphan*/  stub5 (scalar_t__,char*) ; 
 int /*<<< orphan*/  stub6 (int) ; 
 int /*<<< orphan*/  stub7 () ; 

qboolean Item_TextField_HandleKey(itemDef_t *item, int key) {
	char buff[1024];
	int len;
	itemDef_t *newItem = NULL;
	editFieldDef_t *editPtr = (editFieldDef_t*)item->typeData;

	if (item->cvar) {

		memset(buff, 0, sizeof(buff));
		DC->getCVarString(item->cvar, buff, sizeof(buff));
		len = strlen(buff);
		if (editPtr->maxChars && len > editPtr->maxChars) {
			len = editPtr->maxChars;
		}
		if ( key & K_CHAR_FLAG ) {
			key &= ~K_CHAR_FLAG;


			if (key == 'h' - 'a' + 1 )	{	// ctrl-h is backspace
				if ( item->cursorPos > 0 ) {
					memmove( &buff[item->cursorPos - 1], &buff[item->cursorPos], len + 1 - item->cursorPos);
					item->cursorPos--;
					if (item->cursorPos < editPtr->paintOffset) {
						editPtr->paintOffset--;
					}
				}
				DC->setCVar(item->cvar, buff);
	    		return qtrue;
			}


			//
			// ignore any non printable chars
			//
			if ( key < 32 || !item->cvar) {
			    return qtrue;
		    }

			if (item->type == ITEM_TYPE_NUMERICFIELD) {
				if (key < '0' || key > '9') {
					return qfalse;
				}
			}

			if (!DC->getOverstrikeMode()) {
				if (( len == MAX_EDITFIELD - 1 ) || (editPtr->maxChars && len >= editPtr->maxChars)) {
					return qtrue;
				}
				memmove( &buff[item->cursorPos + 1], &buff[item->cursorPos], len + 1 - item->cursorPos );
			} else {
				if (editPtr->maxChars && item->cursorPos >= editPtr->maxChars) {
					return qtrue;
				}
			}

			buff[item->cursorPos] = key;

			DC->setCVar(item->cvar, buff);

			if (item->cursorPos < len + 1) {
				item->cursorPos++;
				if (editPtr->maxPaintChars && item->cursorPos > editPtr->maxPaintChars) {
					editPtr->paintOffset++;
				}
			}

		} else {

			if ( key == K_DEL || key == K_KP_DEL ) {
				if ( item->cursorPos < len ) {
					memmove( buff + item->cursorPos, buff + item->cursorPos + 1, len - item->cursorPos);
					DC->setCVar(item->cvar, buff);
				}
				return qtrue;
			}

			if ( key == K_RIGHTARROW || key == K_KP_RIGHTARROW ) 
			{
				if (editPtr->maxPaintChars && item->cursorPos >= editPtr->maxPaintChars && item->cursorPos < len) {
					item->cursorPos++;
					editPtr->paintOffset++;
					return qtrue;
				}
				if (item->cursorPos < len) {
					item->cursorPos++;
				} 
				return qtrue;
			}

			if ( key == K_LEFTARROW || key == K_KP_LEFTARROW ) 
			{
				if ( item->cursorPos > 0 ) {
					item->cursorPos--;
				}
				if (item->cursorPos < editPtr->paintOffset) {
					editPtr->paintOffset--;
				}
				return qtrue;
			}

			if ( key == K_HOME || key == K_KP_HOME) {// || ( tolower(key) == 'a' && trap_Key_IsDown( K_CTRL ) ) ) {
				item->cursorPos = 0;
				editPtr->paintOffset = 0;
				return qtrue;
			}

			if ( key == K_END || key == K_KP_END)  {// ( tolower(key) == 'e' && trap_Key_IsDown( K_CTRL ) ) ) {
				item->cursorPos = len;
				if(item->cursorPos > editPtr->maxPaintChars) {
					editPtr->paintOffset = len - editPtr->maxPaintChars;
				}
				return qtrue;
			}

			if ( key == K_INS || key == K_KP_INS ) {
				DC->setOverstrikeMode(!DC->getOverstrikeMode());
				return qtrue;
			}
		}

		if (key == K_TAB || key == K_DOWNARROW || key == K_KP_DOWNARROW) {
			newItem = Menu_SetNextCursorItem(item->parent);
			if (newItem && (newItem->type == ITEM_TYPE_EDITFIELD || newItem->type == ITEM_TYPE_NUMERICFIELD)) {
				g_editItem = newItem;
			}
		}

		if (key == K_UPARROW || key == K_KP_UPARROW) {
			newItem = Menu_SetPrevCursorItem(item->parent);
			if (newItem && (newItem->type == ITEM_TYPE_EDITFIELD || newItem->type == ITEM_TYPE_NUMERICFIELD)) {
				g_editItem = newItem;
			}
		}

		if ( key == K_ENTER || key == K_KP_ENTER || key == K_ESCAPE)  {
			return qfalse;
		}

		return qtrue;
	}
	return qfalse;

}