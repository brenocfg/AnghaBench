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
typedef  int /*<<< orphan*/  PyObject ;
typedef  scalar_t__ FcBool ;

/* Variables and functions */
 int /*<<< orphan*/ * Py_False ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_True ; 

__attribute__((used)) static inline PyObject*
pybool(FcBool x) { PyObject *ans = x ? Py_True: Py_False; Py_INCREF(ans); return ans; }