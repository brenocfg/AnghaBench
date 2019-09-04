#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cellRendererButtonClass ;
struct TYPE_5__ {int /*<<< orphan*/  activate; int /*<<< orphan*/  render; int /*<<< orphan*/  get_aligned_area; int /*<<< orphan*/  get_preferred_height; int /*<<< orphan*/  get_preferred_height_for_width; int /*<<< orphan*/  get_preferred_width; int /*<<< orphan*/  get_request_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  get_property; int /*<<< orphan*/  set_property; int /*<<< orphan*/  finalize; int /*<<< orphan*/  dispose; } ;

/* Variables and functions */
 TYPE_3__* GTK_CELL_RENDERER_CLASS (int /*<<< orphan*/ *) ; 
 TYPE_1__* G_OBJECT_CLASS (int /*<<< orphan*/ *) ; 
 int G_PARAM_CONSTRUCT ; 
 int G_PARAM_READWRITE ; 
 int G_PARAM_STATIC_STRINGS ; 
 int /*<<< orphan*/  G_SIGNAL_RUN_LAST ; 
 int /*<<< orphan*/  G_TYPE_FROM_CLASS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_TYPE_NONE ; 
 int /*<<< orphan*/  G_TYPE_STRING ; 
 int /*<<< orphan*/  cellRendererButton_activate ; 
 int /*<<< orphan*/  cellRendererButton_dispose ; 
 int /*<<< orphan*/  cellRendererButton_finalize ; 
 int /*<<< orphan*/  cellRendererButton_get_aligned_area ; 
 int /*<<< orphan*/  cellRendererButton_get_preferred_height ; 
 int /*<<< orphan*/  cellRendererButton_get_preferred_height_for_width ; 
 int /*<<< orphan*/  cellRendererButton_get_preferred_width ; 
 int /*<<< orphan*/  cellRendererButton_get_property ; 
 int /*<<< orphan*/  cellRendererButton_get_request_mode ; 
 int /*<<< orphan*/  cellRendererButton_render ; 
 int /*<<< orphan*/  cellRendererButton_set_property ; 
 int /*<<< orphan*/  clickedSignal ; 
 int /*<<< orphan*/  g_object_class_install_properties (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_param_spec_string (char*,char*,char*,char*,int) ; 
 int /*<<< orphan*/  g_signal_new (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * props ; 

__attribute__((used)) static void cellRendererButton_class_init(cellRendererButtonClass *class)
{
	G_OBJECT_CLASS(class)->dispose = cellRendererButton_dispose;
	G_OBJECT_CLASS(class)->finalize = cellRendererButton_finalize;
	G_OBJECT_CLASS(class)->set_property = cellRendererButton_set_property;
	G_OBJECT_CLASS(class)->get_property = cellRendererButton_get_property;
	GTK_CELL_RENDERER_CLASS(class)->get_request_mode = cellRendererButton_get_request_mode;
	GTK_CELL_RENDERER_CLASS(class)->get_preferred_width = cellRendererButton_get_preferred_width;
	GTK_CELL_RENDERER_CLASS(class)->get_preferred_height_for_width = cellRendererButton_get_preferred_height_for_width;
	GTK_CELL_RENDERER_CLASS(class)->get_preferred_height = cellRendererButton_get_preferred_height;
	// don't provide a get_preferred_width_for_height()
	GTK_CELL_RENDERER_CLASS(class)->get_aligned_area = cellRendererButton_get_aligned_area;
	// don't provide a get_size()
	GTK_CELL_RENDERER_CLASS(class)->render = cellRendererButton_render;
	GTK_CELL_RENDERER_CLASS(class)->activate = cellRendererButton_activate;
	// don't provide a start_editing()

	props[1] = g_param_spec_string("text",
		"Text",
		"Button text",
		"",
		G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS);
	g_object_class_install_properties(G_OBJECT_CLASS(class), 2, props);

	clickedSignal = g_signal_new("clicked",
		G_TYPE_FROM_CLASS(class),
		G_SIGNAL_RUN_LAST,
		0,
		NULL, NULL, NULL,
		G_TYPE_NONE,
		1, G_TYPE_STRING);
}