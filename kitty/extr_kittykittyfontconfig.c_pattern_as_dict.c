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
typedef  int /*<<< orphan*/  FcPattern ;
typedef  int /*<<< orphan*/  FcChar8 ;

/* Variables and functions */
 int /*<<< orphan*/  FC_COLOR ; 
 int /*<<< orphan*/  FC_FAMILY ; 
 int /*<<< orphan*/  FC_FILE ; 
 int /*<<< orphan*/  FC_FULLNAME ; 
 int /*<<< orphan*/  FC_HINTING ; 
 int /*<<< orphan*/  FC_HINT_STYLE ; 
 int /*<<< orphan*/  FC_INDEX ; 
 int /*<<< orphan*/  FC_LCD_FILTER ; 
 int /*<<< orphan*/  FC_OUTLINE ; 
 int /*<<< orphan*/  FC_POSTSCRIPT_NAME ; 
 int /*<<< orphan*/  FC_RGBA ; 
 int /*<<< orphan*/  FC_SCALABLE ; 
 int /*<<< orphan*/  FC_SLANT ; 
 int /*<<< orphan*/  FC_SPACING ; 
 int /*<<< orphan*/  FC_STYLE ; 
 int /*<<< orphan*/  FC_WEIGHT ; 
 scalar_t__ FcPatternGetBool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ FcPatternGetInteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ FcPatternGetString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ FcResultMatch ; 
 int /*<<< orphan*/ * PyDict_New () ; 
 scalar_t__ PyDict_SetItemString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyLong_FromLong (int) ; 
 int /*<<< orphan*/ * PyUnicode_Decode (char const*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pybool (int) ; 
 int /*<<< orphan*/ * pyspacing (int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static inline PyObject*
pattern_as_dict(FcPattern *pat) {
    PyObject *ans = PyDict_New();
    if (ans == NULL) return NULL;
#define PS(x) PyUnicode_Decode((const char*)x, strlen((const char*)x), "UTF-8", "replace")
#define G(type, get, which, conv, name) { \
    type out; PyObject *p; \
    if (get(pat, which, 0, &out) == FcResultMatch) { \
        p = conv(out); if (p == NULL) { Py_CLEAR(ans); return NULL; } \
        if (PyDict_SetItemString(ans, #name, p) != 0) { Py_CLEAR(p); Py_CLEAR(ans); return NULL; } \
        Py_CLEAR(p); \
    }}
#define S(which, key) G(FcChar8*, FcPatternGetString, which, PS, key)
#define I(which, key) G(int, FcPatternGetInteger, which, PyLong_FromLong, key)
#define B(which, key) G(int, FcPatternGetBool, which, pybool, key)
#define E(which, key, conv) G(int, FcPatternGetInteger, which, conv, key)
    S(FC_FILE, path);
    S(FC_FAMILY, family);
    S(FC_STYLE, style);
    S(FC_FULLNAME, full_name);
    S(FC_POSTSCRIPT_NAME, postscript_name);
    I(FC_WEIGHT, weight);
    I(FC_SLANT, slant);
    I(FC_HINT_STYLE, hint_style);
    I(FC_INDEX, index);
    I(FC_RGBA, subpixel);
    I(FC_LCD_FILTER, lcdfilter);
    B(FC_HINTING, hinting);
    B(FC_SCALABLE, scalable);
    B(FC_OUTLINE, outline);
    B(FC_COLOR, color);
    E(FC_SPACING, spacing, pyspacing);

    return ans;
#undef PS
#undef S
#undef I
#undef B
#undef E
#undef G
}