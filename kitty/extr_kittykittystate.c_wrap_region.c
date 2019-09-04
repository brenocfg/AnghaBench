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
struct TYPE_3__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_1__ Region ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyLong_FromUnsignedLong (scalar_t__) ; 
 int /*<<< orphan*/ * PyStructSequence_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyStructSequence_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegionType ; 

__attribute__((used)) static inline PyObject*
wrap_region(Region *r) {
    PyObject *ans = PyStructSequence_New(&RegionType);
    if (ans) {
        PyStructSequence_SET_ITEM(ans, 0, PyLong_FromUnsignedLong(r->left));
        PyStructSequence_SET_ITEM(ans, 1, PyLong_FromUnsignedLong(r->top));
        PyStructSequence_SET_ITEM(ans, 2, PyLong_FromUnsignedLong(r->right));
        PyStructSequence_SET_ITEM(ans, 3, PyLong_FromUnsignedLong(r->bottom));
        PyStructSequence_SET_ITEM(ans, 4, PyLong_FromUnsignedLong(r->right - r->left + 1));
        PyStructSequence_SET_ITEM(ans, 5, PyLong_FromUnsignedLong(r->bottom - r->top + 1));
    }
    return ans;
}