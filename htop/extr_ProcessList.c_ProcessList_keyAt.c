#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* title; } ;
struct TYPE_6__ {TYPE_1__* settings; } ;
struct TYPE_5__ {size_t* fields; } ;
typedef  TYPE_2__ ProcessList ;
typedef  size_t ProcessField ;

/* Variables and functions */
 size_t COMM ; 
 TYPE_3__* Process_fields ; 
 int strlen (char const*) ; 

ProcessField ProcessList_keyAt(ProcessList* this, int at) {
   int x = 0;
   ProcessField* fields = this->settings->fields;
   ProcessField field;
   for (int i = 0; (field = fields[i]); i++) {
      const char* title = Process_fields[field].title;
      if (!title) title = "- ";
      int len = strlen(title);
      if (at >= x && at <= x + len) {
         return field;
      }
      x += len;
   }
   return COMM;
}