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
struct TYPE_3__ {int ch; scalar_t__* cc_idx; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ CPUCell ;

/* Variables and functions */
 int /*<<< orphan*/  PyObject_Print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int arraysz (scalar_t__*) ; 
 int codepoint_for_mark (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static inline void
output_cell_fallback_data(CPUCell *cell, bool bold, bool italic, bool emoji_presentation, PyObject *face, bool new_face) {
    printf("U+%x ", cell->ch);
    for (unsigned i = 0; i < arraysz(cell->cc_idx) && cell->cc_idx[i]; i++) {
        printf("U+%x ", codepoint_for_mark(cell->cc_idx[i]));
    }
    if (bold) printf("bold ");
    if (italic) printf("italic ");
    if (emoji_presentation) printf("emoji_presentation ");
    PyObject_Print(face, stdout, 0);
    if (new_face) printf(" (new face)");
    printf("\n");
}