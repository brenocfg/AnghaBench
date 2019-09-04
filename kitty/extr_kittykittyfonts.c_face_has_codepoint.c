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
typedef  int /*<<< orphan*/  char_type ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 scalar_t__ glyph_id_for_codepoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
face_has_codepoint(PyObject* face, char_type cp) {
    return glyph_id_for_codepoint(face, cp) > 0;
}