#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  char_type ;
struct TYPE_2__ {int /*<<< orphan*/  face; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Face ;

/* Variables and functions */
 unsigned int FT_Get_Char_Index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int
glyph_id_for_codepoint(PyObject *s, char_type cp) {
    return FT_Get_Char_Index(((Face*)s)->face, cp);
}