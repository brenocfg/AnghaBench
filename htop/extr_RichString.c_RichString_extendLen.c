#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int chlen; int /*<<< orphan*/  chptr; int /*<<< orphan*/  chstr; } ;
typedef  TYPE_1__ RichString ;

/* Variables and functions */
 int RICHSTRING_MAXLEN ; 
 int /*<<< orphan*/  RichString_setChar (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  charBytes (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xMalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xRealloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void RichString_extendLen(RichString* this, int len) {
   if (this->chlen <= RICHSTRING_MAXLEN) {
      if (len > RICHSTRING_MAXLEN) {
         this->chptr = xMalloc(charBytes(len + 1));
         memcpy(this->chptr, this->chstr, charBytes(this->chlen));
      }
   } else {
      if (len <= RICHSTRING_MAXLEN) {
         memcpy(this->chstr, this->chptr, charBytes(len));
         free(this->chptr);
         this->chptr = this->chstr;
      } else {
         this->chptr = xRealloc(this->chptr, charBytes(len + 1));
      }
   }

   RichString_setChar(this, len, 0);
   this->chlen = len;
}