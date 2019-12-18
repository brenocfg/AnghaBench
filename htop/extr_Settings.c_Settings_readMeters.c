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
struct TYPE_4__ {char** names; } ;
typedef  TYPE_2__ Settings ;

/* Variables and functions */
 char** String_split (char*,char,int*) ; 
 char* String_trim (char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void Settings_readMeters(Settings* this, char* line, int column) {
   char* trim = String_trim(line);
   int nIds;
   char** ids = String_split(trim, ' ', &nIds);
   free(trim);
   this->columns[column].names = ids;
}