#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int chtype ;
struct TYPE_3__ {int* chptr; scalar_t__ chlen; } ;
typedef  TYPE_1__ RichString ;

/* Variables and functions */
 int CLAMP (int,int /*<<< orphan*/ ,scalar_t__) ; 

void RichString_setAttrn(RichString* this, int attrs, int start, int finish) {
   chtype* ch = this->chptr + start;
   finish = CLAMP(finish, 0, this->chlen - 1);
   for (int i = start; i <= finish; i++) {
      *ch = (*ch & 0xff) | attrs;
      ch++;
   }
}