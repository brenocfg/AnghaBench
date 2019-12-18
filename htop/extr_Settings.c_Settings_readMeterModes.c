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
struct TYPE_5__ {TYPE_1__* columns; } ;
struct TYPE_4__ {int len; int* modes; } ;
typedef  TYPE_2__ Settings ;

/* Variables and functions */
 int /*<<< orphan*/  String_freeArray (char**) ; 
 char** String_split (char*,char,int*) ; 
 char* String_trim (char*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int* xCalloc (int,int) ; 

__attribute__((used)) static void Settings_readMeterModes(Settings* this, char* line, int column) {
   char* trim = String_trim(line);
   int nIds;
   char** ids = String_split(trim, ' ', &nIds);
   free(trim);
   int len = 0;
   for (int i = 0; ids[i]; i++) {
      len++;
   }
   this->columns[column].len = len;
   int* modes = xCalloc(len, sizeof(int));
   for (int i = 0; i < len; i++) {
      modes[i] = atoi(ids[i]);
   }
   String_freeArray(ids);
   this->columns[column].modes = modes;
}