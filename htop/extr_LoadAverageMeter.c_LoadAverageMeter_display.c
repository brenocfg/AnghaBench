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
struct TYPE_2__ {int /*<<< orphan*/ * values; } ;
typedef  int /*<<< orphan*/  RichString ;
typedef  int /*<<< orphan*/  Object ;
typedef  TYPE_1__ Meter ;

/* Variables and functions */
 int /*<<< orphan*/ * CRT_colors ; 
 size_t LOAD_AVERAGE_FIFTEEN ; 
 size_t LOAD_AVERAGE_FIVE ; 
 size_t LOAD_AVERAGE_ONE ; 
 int /*<<< orphan*/  RichString_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RichString_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xSnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LoadAverageMeter_display(Object* cast, RichString* out) {
   Meter* this = (Meter*)cast;
   char buffer[20];
   xSnprintf(buffer, sizeof(buffer), "%.2f ", this->values[0]);
   RichString_write(out, CRT_colors[LOAD_AVERAGE_ONE], buffer);
   xSnprintf(buffer, sizeof(buffer), "%.2f ", this->values[1]);
   RichString_append(out, CRT_colors[LOAD_AVERAGE_FIVE], buffer);
   xSnprintf(buffer, sizeof(buffer), "%.2f ", this->values[2]);
   RichString_append(out, CRT_colors[LOAD_AVERAGE_FIFTEEN], buffer);
}