#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ob_refcnt; int /*<<< orphan*/ * ob_type; } ;
struct TYPE_7__ {scalar_t__ ob_size; TYPE_1__ ob_base; } ;
struct TYPE_8__ {TYPE_2__ ob_base; } ;
typedef  scalar_t__ Py_ssize_t ;
typedef  TYPE_3__ PyBytesObject ;

/* Variables and functions */
 scalar_t__ GATHER_MAX_LEN ; 
 int /*<<< orphan*/  PyBytes_Type ; 
 scalar_t__ PyErr_NoMemory () ; 
 TYPE_3__* malloc (scalar_t__) ; 

__attribute__((used)) static inline PyBytesObject*
Bytes_FromSize(size_t size)
{
  PyBytesObject* result;
  if(!(result = malloc(sizeof(PyBytesObject) + GATHER_MAX_LEN)))
    return (PyBytesObject*)PyErr_NoMemory();

  result->ob_base.ob_base.ob_refcnt = 1;
  result->ob_base.ob_base.ob_type = &PyBytes_Type;
  result->ob_base.ob_size = (Py_ssize_t)size;

  return result;
}