#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ mBRACKETED_PASTE; } ;
struct TYPE_7__ {TYPE_1__ modes; } ;
typedef  TYPE_2__ Screen ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  BRACKETED_PASTE_END ; 
 int /*<<< orphan*/  BRACKETED_PASTE_START ; 
 int /*<<< orphan*/  CSI ; 
 int /*<<< orphan*/  PyBytes_AS_STRING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyBytes_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  write_escape_code_to_child (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_to_child (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject*
paste(Screen *self, PyObject *bytes) {
    if (self->modes.mBRACKETED_PASTE) write_escape_code_to_child(self, CSI, BRACKETED_PASTE_START);
    write_to_child(self, PyBytes_AS_STRING(bytes), PyBytes_GET_SIZE(bytes));
    if (self->modes.mBRACKETED_PASTE) write_escape_code_to_child(self, CSI, BRACKETED_PASTE_END);
    Py_RETURN_NONE;
}