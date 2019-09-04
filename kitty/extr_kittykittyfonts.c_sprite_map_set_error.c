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

/* Variables and functions */
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 

__attribute__((used)) static inline void
sprite_map_set_error(int error) {
    switch(error) {
        case 1:
            PyErr_NoMemory(); break;
        case 2:
            PyErr_SetString(PyExc_RuntimeError, "Out of texture space for sprites"); break;
        default:
            PyErr_SetString(PyExc_RuntimeError, "Unknown error occurred while allocating sprites"); break;
    }
}