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
struct TYPE_2__ {int /*<<< orphan*/ * values; int /*<<< orphan*/  total; } ;
typedef  int /*<<< orphan*/  RichString ;
typedef  int /*<<< orphan*/  Object ;
typedef  TYPE_1__ Meter ;

/* Variables and functions */
 int /*<<< orphan*/ * CRT_colors ; 
 size_t MEMORY_BUFFERS_TEXT ; 
 size_t MEMORY_CACHE ; 
 size_t MEMORY_USED ; 
 size_t METER_TEXT ; 
 size_t METER_VALUE ; 
 int /*<<< orphan*/  Meter_humanUnit (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RichString_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RichString_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void MemoryMeter_display(Object* cast, RichString* out) {
   char buffer[50];
   Meter* this = (Meter*)cast;
   RichString_write(out, CRT_colors[METER_TEXT], ":");
   Meter_humanUnit(buffer, this->total, 50);
   RichString_append(out, CRT_colors[METER_VALUE], buffer);
   Meter_humanUnit(buffer, this->values[0], 50);
   RichString_append(out, CRT_colors[METER_TEXT], " used:");
   RichString_append(out, CRT_colors[MEMORY_USED], buffer);
   Meter_humanUnit(buffer, this->values[1], 50);
   RichString_append(out, CRT_colors[METER_TEXT], " buffers:");
   RichString_append(out, CRT_colors[MEMORY_BUFFERS_TEXT], buffer);
   Meter_humanUnit(buffer, this->values[2], 50);
   RichString_append(out, CRT_colors[METER_TEXT], " cache:");
   RichString_append(out, CRT_colors[MEMORY_CACHE], buffer);
}