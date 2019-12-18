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
struct TYPE_2__ {int flags; scalar_t__ name; } ;
typedef  int ProcessField ;

/* Variables and functions */
 int NULL_PROCESSFIELD ; 
 int Platform_numberOfFields ; 
 TYPE_1__* Process_fields ; 
 int /*<<< orphan*/  String_freeArray (char**) ; 
 char** String_split (char*,char,int*) ; 
 char* String_trim (char const*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void readFields(ProcessField* fields, int* flags, const char* line) {
   char* trim = String_trim(line);
   int nIds;
   char** ids = String_split(trim, ' ', &nIds);
   free(trim);
   int i, j;
   *flags = 0;
   for (j = 0, i = 0; i < Platform_numberOfFields && ids[i]; i++) {
      // This "+1" is for compatibility with the older enum format.
      int id = atoi(ids[i]) + 1;
      if (id > 0 && Process_fields[id].name && id < Platform_numberOfFields) {
         fields[j] = id;
         *flags |= Process_fields[id].flags;
         j++;
      }
   }
   fields[j] = NULL_PROCESSFIELD;
   String_freeArray(ids);
}