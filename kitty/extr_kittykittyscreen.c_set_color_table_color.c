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
typedef  int /*<<< orphan*/  Screen ;
typedef  char PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK (char*,char*,unsigned int,char*) ; 

void
set_color_table_color(Screen *self, unsigned int code, PyObject *color) {
    if (color == NULL) { CALLBACK("set_color_table_color", "Is", code, ""); }
    else { CALLBACK("set_color_table_color", "IO", code, color); }
}