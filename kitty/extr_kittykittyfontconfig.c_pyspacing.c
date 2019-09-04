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

/* Variables and functions */
#define  FC_CHARCELL 131 
#define  FC_DUAL 130 
#define  FC_MONO 129 
#define  FC_PROPORTIONAL 128 
 int /*<<< orphan*/ * PyUnicode_FromString (char*) ; 

__attribute__((used)) static inline PyObject*
pyspacing(int val) {
#define S(x) case FC_##x: return PyUnicode_FromString(#x)
    switch(val) { S(PROPORTIONAL); S(DUAL); S(MONO); S(CHARCELL); default: return PyUnicode_FromString("UNKNOWN"); }
#undef S
}