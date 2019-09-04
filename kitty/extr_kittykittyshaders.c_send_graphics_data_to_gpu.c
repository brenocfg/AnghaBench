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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  vertices; } ;
typedef  TYPE_1__ ImageRenderData ;
typedef  int /*<<< orphan*/  GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GL_STREAM_DRAW ; 
 int /*<<< orphan*/  GL_WRITE_ONLY ; 
 int /*<<< orphan*/ * alloc_and_map_vao_buffer (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unmap_vao_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
send_graphics_data_to_gpu(size_t image_count, ssize_t gvao_idx, const ImageRenderData *render_data) {
    size_t sz = sizeof(GLfloat) * 16 * image_count;
    GLfloat *a = alloc_and_map_vao_buffer(gvao_idx, sz, 0, GL_STREAM_DRAW, GL_WRITE_ONLY);
    for (size_t i = 0; i < image_count; i++, a += 16) memcpy(a, render_data[i].vertices, sizeof(render_data[0].vertices));
    unmap_vao_buffer(gvao_idx, 0); a = NULL;
}