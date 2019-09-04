#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  used_storage; } ;
struct TYPE_6__ {scalar_t__ used_storage; int /*<<< orphan*/  load_data; scalar_t__ texture_id; } ;
typedef  TYPE_1__ Image ;
typedef  TYPE_2__ GraphicsManager ;

/* Variables and functions */
 int /*<<< orphan*/  free_load_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_refs_data (TYPE_1__*) ; 
 int /*<<< orphan*/  free_texture (scalar_t__*) ; 

__attribute__((used)) static inline void
free_image(GraphicsManager *self, Image *img) {
    if (img->texture_id) free_texture(&img->texture_id);
    free_refs_data(img);
    free_load_data(&(img->load_data));
    self->used_storage -= img->used_storage;
}