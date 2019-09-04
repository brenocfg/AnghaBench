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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int Py_Main (int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int run_embedded(const char* exe_dir_, int argc, wchar_t **argv) {
    (void)exe_dir_;
#ifdef __APPLE__
    wchar_t *exe_dir = Py_DecodeLocale(exe_dir_, NULL);
    if (exe_dir == NULL) { fprintf(stderr, "Fatal error: cannot decode exe_dir\n"); return 1; }
    set_bundle_exe_dir(exe_dir);
#endif
    return Py_Main(argc, argv);
}