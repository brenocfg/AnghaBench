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
struct TYPE_3__ {int /*<<< orphan*/  attributes; int /*<<< orphan*/  pixel_size; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y_origin; int /*<<< orphan*/  x_origin; int /*<<< orphan*/  colormap_size; int /*<<< orphan*/  colormap_length; int /*<<< orphan*/  colormap_index; int /*<<< orphan*/  image_type; int /*<<< orphan*/  colormap_type; int /*<<< orphan*/  id_length; } ;
typedef  TYPE_1__ TargaHeader ;

/* Variables and functions */
 int /*<<< orphan*/  Sys_Printf (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void TargaError( TargaHeader *t, const char *message ){
	Sys_Printf( "%s\n:TargaHeader:\nuint8 id_length = %i;\nuint8 colormap_type = %i;\nuint8 image_type = %i;\nuint16 colormap_index = %i;\nuint16 colormap_length = %i;\nuint8 colormap_size = %i;\nuint16 x_origin = %i;\nuint16 y_origin = %i;\nuint16 width = %i;\nuint16 height = %i;\nuint8 pixel_size = %i;\nuint8 attributes = %i;\n", message, t->id_length, t->colormap_type, t->image_type, t->colormap_index, t->colormap_length, t->colormap_size, t->x_origin, t->y_origin, t->width, t->height, t->pixel_size, t->attributes );
}