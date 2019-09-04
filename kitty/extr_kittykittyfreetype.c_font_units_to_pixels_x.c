#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* face; } ;
struct TYPE_8__ {TYPE_2__* size; } ;
struct TYPE_6__ {int /*<<< orphan*/  x_scale; } ;
struct TYPE_7__ {TYPE_1__ metrics; } ;
typedef  TYPE_4__ Face ;

/* Variables and functions */
 scalar_t__ FT_MulFix (int,int /*<<< orphan*/ ) ; 
 int ceil (double) ; 

__attribute__((used)) static inline int
font_units_to_pixels_x(Face *self, int x) {
    return ceil((double)FT_MulFix(x, self->face->size->metrics.x_scale) / 64.0);
}