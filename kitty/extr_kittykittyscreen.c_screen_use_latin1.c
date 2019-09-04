#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int use_latin1; scalar_t__ utf8_codepoint; scalar_t__ utf8_state; } ;
typedef  TYPE_1__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_False ; 
 int /*<<< orphan*/  Py_True ; 

void
screen_use_latin1(Screen *self, bool on) {
    self->use_latin1 = on; self->utf8_state = 0; self->utf8_codepoint = 0;
    CALLBACK("use_utf8", "O", on ? Py_False : Py_True);
}