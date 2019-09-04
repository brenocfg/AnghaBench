#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bold; int italic; int /*<<< orphan*/  face; } ;
typedef  TYPE_1__ Font ;

/* Variables and functions */
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_maps (TYPE_1__*) ; 

__attribute__((used)) static inline void
del_font(Font *f) {
    Py_CLEAR(f->face);
    free_maps(f);
    f->bold = false; f->italic = false;
}