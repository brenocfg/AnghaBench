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
struct TYPE_3__ {int nfont; int /*<<< orphan*/ * fonts; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ FcFontSet ;

/* Variables and functions */
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pattern_as_dict (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline PyObject*
font_set(FcFontSet *fs) {
    PyObject *ans = PyTuple_New(fs->nfont);
    if (ans == NULL) return NULL;
    for (int i = 0; i < fs->nfont; i++) {
        PyObject *d = pattern_as_dict(fs->fonts[i]);
        if (d == NULL) { Py_CLEAR(ans); break; }
        PyTuple_SET_ITEM(ans, i, d);
    }
    return ans;
}