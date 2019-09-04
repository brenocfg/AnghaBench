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
struct TYPE_3__ {int /*<<< orphan*/  cell_size; int /*<<< orphan*/  alt_grman; int /*<<< orphan*/  main_grman; } ;
typedef  TYPE_1__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  grman_rescale (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
screen_rescale_images(Screen *self) {
    grman_rescale(self->main_grman, self->cell_size);
    grman_rescale(self->alt_grman, self->cell_size);
}