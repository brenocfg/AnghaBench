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
typedef  int /*<<< orphan*/  Generator ;

/* Variables and functions */
 int /*<<< orphan*/ * Generator_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject*
Generator_send(Generator* self, PyObject* arg)
{
  return Generator_next(self);
}