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
typedef  int /*<<< orphan*/  md3XyzNormal_t ;
typedef  int /*<<< orphan*/  md3Triangle_t ;
typedef  int /*<<< orphan*/  md3Surface_t ;
typedef  int /*<<< orphan*/  md3St_t ;
typedef  int /*<<< orphan*/  md3Shader_t ;
struct TYPE_3__ {int (* get_surface_shader_count ) (void*,size_t) ;int (* get_surface_face_count ) (void*,size_t) ;int (* get_surface_vertex_count ) (void*,size_t) ;} ;
typedef  TYPE_1__ DeepmindModelGetters ;

/* Variables and functions */
 int stub1 (void*,size_t) ; 
 int stub2 (void*,size_t) ; 
 int stub3 (void*,size_t) ; 

__attribute__((used)) static size_t SurfaceSize(              //
    size_t surf_idx,                    //
    const DeepmindModelGetters* model,  //
    void* model_data) {
  size_t res;
  res = sizeof(md3Surface_t);
  res += model->get_surface_shader_count(model_data, surf_idx) *
      sizeof(md3Shader_t);
  res += model->get_surface_face_count(model_data, surf_idx) *
      sizeof(md3Triangle_t);
  res += model->get_surface_vertex_count(model_data, surf_idx) *
      (sizeof(md3St_t) + sizeof(md3XyzNormal_t));
  return res;
}