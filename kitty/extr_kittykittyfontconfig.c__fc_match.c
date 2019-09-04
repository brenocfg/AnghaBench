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
typedef  int /*<<< orphan*/  FcResult ;
typedef  int /*<<< orphan*/  FcPattern ;

/* Variables and functions */
 int /*<<< orphan*/  FcConfigSubstitute (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FcDefaultSubstitute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FcFontMatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FcMatchPattern ; 
 int /*<<< orphan*/  FcPatternDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_KeyError ; 
 int /*<<< orphan*/ * pattern_as_dict (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline PyObject*
_fc_match(FcPattern *pat) {
    FcPattern *match = NULL;
    PyObject *ans = NULL;
    FcResult result;
    FcConfigSubstitute(NULL, pat, FcMatchPattern);
    FcDefaultSubstitute(pat);
    /* printf("fc_match = %s\n", FcNameUnparse(pat)); */
    match = FcFontMatch(NULL, pat, &result);
    if (match == NULL) { PyErr_SetString(PyExc_KeyError, "FcFontMatch() failed"); goto end; }
    ans = pattern_as_dict(match);
end:
    if (match) FcPatternDestroy(match);
    return ans;
}