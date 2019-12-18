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
typedef  scalar_t__ EnvCApi_PropertyAttributes ;

/* Variables and functions */
 int /*<<< orphan*/  PyDict_SetItemString (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyInt_FromLong (int) ; 

__attribute__((used)) static void PropertyCallback(void* userdata, const char* key,
                             EnvCApi_PropertyAttributes attributes) {
  PyObject* dictionary = (PyObject*)userdata;
  PyDict_SetItemString(dictionary, key, PyInt_FromLong((int)attributes));
}