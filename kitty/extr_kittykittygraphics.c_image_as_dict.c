#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data_sz; int /*<<< orphan*/  data; scalar_t__ is_4byte_aligned; } ;
struct TYPE_5__ {TYPE_1__ load_data; scalar_t__ data_loaded; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  internal_id; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  client_id; int /*<<< orphan*/  texture_id; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ Image ;

/* Variables and functions */
 int /*<<< orphan*/ * Py_BuildValue (char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  Py_False ; 
 int /*<<< orphan*/  Py_True ; 

__attribute__((used)) static inline PyObject*
image_as_dict(Image *img) {
#define U(x) #x, img->x
    return Py_BuildValue("{sI sI sI sI sI sI sO sO sN}",
        U(texture_id), U(client_id), U(width), U(height), U(internal_id), U(refcnt),
        "data_loaded", img->data_loaded ? Py_True : Py_False,
        "is_4byte_aligned", img->load_data.is_4byte_aligned ? Py_True : Py_False,
        "data", Py_BuildValue("y#", img->load_data.data, img->load_data.data_sz)
    );
#undef U

}