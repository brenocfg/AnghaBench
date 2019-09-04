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
struct TYPE_7__ {scalar_t__ (* tp_alloc ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/ * face; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Face ;
typedef  int /*<<< orphan*/  FONTS_DATA_HANDLE ;

/* Variables and functions */
 int FT_New_Face (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ **) ; 
 TYPE_2__ Face_Type ; 
 int /*<<< orphan*/  Py_CLEAR (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_None ; 
 int /*<<< orphan*/  init_ft_face (TYPE_1__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  library ; 
 int /*<<< orphan*/  set_freetype_error (char*,int) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

PyObject*
face_from_path(const char *path, int index, FONTS_DATA_HANDLE fg) {
    Face *ans = (Face*)Face_Type.tp_alloc(&Face_Type, 0);
    if (ans == NULL) return NULL;
    int error;
    error = FT_New_Face(library, path, index, &ans->face);
    if (error) { set_freetype_error("Failed to load face, with error:", error); ans->face = NULL; return NULL; }
    if (!init_ft_face(ans, Py_None, true, 3, fg)) { Py_CLEAR(ans); return NULL; }
    return (PyObject*)ans;
}