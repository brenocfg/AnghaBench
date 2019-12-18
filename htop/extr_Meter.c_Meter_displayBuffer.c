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
typedef  int /*<<< orphan*/  Meter ;

/* Variables and functions */
 int /*<<< orphan*/ * CRT_colors ; 
 size_t* Meter_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Object_display (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Object_displayFn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RichString_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline void Meter_displayBuffer(Meter* this, char* buffer, RichString* out) {
   if (Object_displayFn(this)) {
      Object_display(this, out);
   } else {
      RichString_write(out, CRT_colors[Meter_attributes(this)[0]], buffer);
   }
}