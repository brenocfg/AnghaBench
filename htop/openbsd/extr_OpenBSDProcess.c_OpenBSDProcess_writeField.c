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
typedef  int /*<<< orphan*/  RichString ;
typedef  int ProcessField ;
typedef  int /*<<< orphan*/  Process ;

/* Variables and functions */
 int* CRT_colors ; 
 size_t DEFAULT_COLOR ; 
 int /*<<< orphan*/  Process_writeField (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RichString_append (int /*<<< orphan*/ *,int,char*) ; 

void OpenBSDProcess_writeField(Process* this, RichString* str, ProcessField field) {
   //OpenBSDProcess* fp = (OpenBSDProcess*) this;
   char buffer[256]; buffer[255] = '\0';
   int attr = CRT_colors[DEFAULT_COLOR];
   //int n = sizeof(buffer) - 1;
   switch (field) {
   // add OpenBSD-specific fields here
   default:
      Process_writeField(this, str, field);
      return;
   }
   RichString_append(str, attr, buffer);
}