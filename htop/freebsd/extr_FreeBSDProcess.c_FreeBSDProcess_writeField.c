#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int /*<<< orphan*/  jname; int /*<<< orphan*/  jid; } ;
typedef  int /*<<< orphan*/  RichString ;
typedef  scalar_t__ ProcessField ;
typedef  int /*<<< orphan*/  Process ;
typedef  TYPE_1__ FreeBSDProcess ;

/* Variables and functions */
 int* CRT_colors ; 
 size_t DEFAULT_COLOR ; 
#define  JAIL 129 
#define  JID 128 
 char* Process_pidFormat ; 
 int /*<<< orphan*/  Process_writeField (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  RichString_append (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  xSnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

void FreeBSDProcess_writeField(Process* this, RichString* str, ProcessField field) {
   FreeBSDProcess* fp = (FreeBSDProcess*) this;
   char buffer[256]; buffer[255] = '\0';
   int attr = CRT_colors[DEFAULT_COLOR];
   int n = sizeof(buffer) - 1;
   switch ((int) field) {
   // add FreeBSD-specific fields here
   case JID: xSnprintf(buffer, n, Process_pidFormat, fp->jid); break;
   case JAIL:{
      xSnprintf(buffer, n, "%-11s ", fp->jname); break;
      if (buffer[11] != '\0') {
         buffer[11] = ' ';
         buffer[12] = '\0';
      }
      break;
   }
   default:
      Process_writeField(this, str, field);
      return;
   }
   RichString_append(str, attr, buffer);
}