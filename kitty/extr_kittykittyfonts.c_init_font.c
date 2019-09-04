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
struct TYPE_3__ {int bold; int italic; int emoji_presentation; int /*<<< orphan*/ * face; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Font ;

/* Variables and functions */
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
init_font(Font *f, PyObject *face, bool bold, bool italic, bool emoji_presentation) {
    f->face = face; Py_INCREF(f->face);
    f->bold = bold; f->italic = italic; f->emoji_presentation = emoji_presentation;
    return true;
}