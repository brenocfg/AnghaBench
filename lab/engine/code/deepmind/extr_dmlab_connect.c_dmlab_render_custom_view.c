#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  (* MakeCurrent ) () ;} ;
struct TYPE_10__ {TYPE_3__* context; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_1__ custom_view; } ;
struct TYPE_9__ {int current_screen_rendered; TYPE_2__ pbos; } ;
typedef  TYPE_3__ GameContext ;
typedef  TYPE_4__ DeepmindContext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_PIXEL_PACK_BUFFER ; 
 int /*<<< orphan*/  GL_READ_ONLY ; 
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_STREAM_READ ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  SCR_RenderCustomView () ; 
 TYPE_4__* dmlab_context () ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void const*,int) ; 
 int /*<<< orphan*/  qglBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglBufferData (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglGenBuffers (int,int /*<<< orphan*/ *) ; 
 void* qglMapBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglReadPixels (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglUnmapBuffer (int /*<<< orphan*/ ) ; 
 TYPE_5__ re ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void dmlab_render_custom_view(
    int width, int height, unsigned char* buffer) {
  re.MakeCurrent();
  DeepmindContext* ctx = dmlab_context();
  GameContext* gc = ctx->context;

  SCR_RenderCustomView();

  gc->current_screen_rendered = false;

  if (!gc->pbos.custom_view.id) {
    qglGenBuffers(1, &gc->pbos.custom_view.id);
  }
  qglBindBuffer(GL_PIXEL_PACK_BUFFER, gc->pbos.custom_view.id);
  int size = width * height * 3;
  if (gc->pbos.custom_view.size < size) {
    gc->pbos.custom_view.size = size;
    qglBufferData(GL_PIXEL_PACK_BUFFER, size, NULL, GL_STREAM_READ);
  }

  qglReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, 0);
  const void* pixel_buffer = qglMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
  memcpy(buffer, pixel_buffer, size);
  qglUnmapBuffer(GL_PIXEL_PACK_BUFFER);
  qglBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
}