#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* value; } ;
struct TYPE_7__ {char* eventHandlerState; } ;
typedef  TYPE_1__ Panel ;
typedef  TYPE_2__ ListItem ;
typedef  int /*<<< orphan*/  HandlerResult ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_LOOP ; 
 int ERR ; 
 int /*<<< orphan*/  HANDLED ; 
 int /*<<< orphan*/  IGNORED ; 
 scalar_t__ Panel_get (TYPE_1__*,int) ; 
 int /*<<< orphan*/  Panel_setSelected (TYPE_1__*,int) ; 
 int Panel_size (TYPE_1__*) ; 
 scalar_t__ isalnum (int) ; 
 int strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 char* xCalloc (int,int) ; 

HandlerResult Panel_selectByTyping(Panel* this, int ch) {
   int size = Panel_size(this);
   if (!this->eventHandlerState)
      this->eventHandlerState = xCalloc(100, sizeof(char));
   char* buffer = this->eventHandlerState;

   if (ch > 0 && ch < 255 && isalnum(ch)) {
      int len = strlen(buffer);
      if (len < 99) {
         buffer[len] = ch;
         buffer[len+1] = '\0';
      }
      for (int try = 0; try < 2; try++) {
         len = strlen(buffer);
         for (int i = 0; i < size; i++) {
            char* cur = ((ListItem*) Panel_get(this, i))->value;
            while (*cur == ' ') cur++;
            if (strncasecmp(cur, buffer, len) == 0) {
               Panel_setSelected(this, i);
               return HANDLED;
            }
         }
         // if current word did not match,
         // retry considering the character the start of a new word.
         buffer[0] = ch;
         buffer[1] = '\0';
      }
      return HANDLED;
   } else if (ch != ERR) {
      buffer[0] = '\0';
   }
   if (ch == 13) {
      return BREAK_LOOP;
   }
   return IGNORED;
}