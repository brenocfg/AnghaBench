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
typedef  int /*<<< orphan*/  FcPattern ;
typedef  int /*<<< orphan*/  FcCharSet ;

/* Variables and functions */
 int /*<<< orphan*/  AP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FC_CHARSET ; 
 int /*<<< orphan*/  FcCharSetAddChar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * FcCharSetCreate () ; 
 int /*<<< orphan*/  FcCharSetDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FcPatternAddCharSet ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/ * char_buf ; 

__attribute__((used)) static inline void
add_charset(FcPattern *pat, size_t num) {
    FcCharSet *charset = NULL;
    if (num) {
        charset = FcCharSetCreate();
        if (charset == NULL) { PyErr_NoMemory(); goto end; }
        for (size_t i = 0; i < num; i++) {
            if (!FcCharSetAddChar(charset, char_buf[i])) {
                PyErr_SetString(PyExc_RuntimeError, "Failed to add character to fontconfig charset");
                goto end;
            }
        }
        AP(FcPatternAddCharSet, FC_CHARSET, charset, "charset");
    }
end:
    if (charset != NULL) FcCharSetDestroy(charset);
}