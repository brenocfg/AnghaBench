#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* normal; void** xyz; } ;
typedef  TYPE_1__ md3XyzNormal_t ;
struct TYPE_10__ {void** indexes; } ;
typedef  TYPE_2__ md3Triangle_t ;
struct TYPE_11__ {void* ofsEnd; void* ofsXyzNormals; void* ofsSt; void* ofsTriangles; void* ofsShaders; void* numTriangles; void* numVerts; void* numShaders; void* numFrames; scalar_t__ flags; int /*<<< orphan*/  name; void* ident; } ;
typedef  TYPE_3__ md3Surface_t ;
struct TYPE_12__ {int /*<<< orphan*/ * st; } ;
typedef  TYPE_4__ md3St_t ;
struct TYPE_13__ {scalar_t__ shaderIndex; int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ md3Shader_t ;
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  aabb_t ;
struct TYPE_14__ {size_t (* get_surface_shader_count ) (void*,size_t) ;size_t (* get_surface_vertex_count ) (void*,size_t) ;size_t (* get_surface_face_count ) (void*,size_t) ;int /*<<< orphan*/  (* get_surface_vertex_normal ) (void*,size_t,size_t,float*) ;int /*<<< orphan*/  (* get_surface_vertex_location ) (void*,size_t,size_t,float*) ;int /*<<< orphan*/  (* get_surface_vertex_st ) (void*,size_t,size_t,float*) ;int /*<<< orphan*/  (* get_surface_face ) (void*,size_t,size_t,int*) ;int /*<<< orphan*/  (* get_surface_shader ) (void*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_surface_name ) (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_6__ DeepmindModelGetters ;

/* Variables and functions */
 int /*<<< orphan*/  AABBExtendByPoint (int /*<<< orphan*/ *,float*) ; 
 int /*<<< orphan*/  LittleFloat (float) ; 
 void* LittleLong (int) ; 
 void* LittleShort (short) ; 
 int /*<<< orphan*/  MAX_QPATH ; 
 int MD3_IDENT ; 
 float MD3_XYZ_SCALE ; 
 int /*<<< orphan*/  NormalToLatLong (float*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t stub2 (void*,size_t) ; 
 size_t stub3 (void*,size_t) ; 
 size_t stub4 (void*,size_t) ; 
 int /*<<< orphan*/  stub5 (void*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (void*,size_t,size_t,int*) ; 
 int /*<<< orphan*/  stub7 (void*,size_t,size_t,float*) ; 
 int /*<<< orphan*/  stub8 (void*,size_t,size_t,float*) ; 
 int /*<<< orphan*/  stub9 (void*,size_t,size_t,float*) ; 

__attribute__((used)) static void SerialiseSurface(           //
    size_t surf_idx,                    //
    const DeepmindModelGetters* model,  //
    void* model_data,                   //
    md3Surface_t* md3_surf,             //
    aabb_t* bbox) {
  // Fill surface header.
  md3_surf->ident = LittleLong(MD3_IDENT);
  model->get_surface_name(model_data, surf_idx, MAX_QPATH, md3_surf->name);
  md3_surf->flags = 0;
  md3_surf->numFrames = LittleLong(1);
  size_t num_shaders = model->get_surface_shader_count(model_data, surf_idx);
  md3_surf->numShaders = LittleLong(num_shaders);
  size_t num_verts = model->get_surface_vertex_count(model_data, surf_idx);
  md3_surf->numVerts = LittleLong(num_verts);
  size_t num_triangles = model->get_surface_face_count(model_data, surf_idx);
  md3_surf->numTriangles = LittleLong(num_triangles);
  size_t ofs_shaders = sizeof(md3Surface_t);
  md3_surf->ofsShaders = LittleLong(ofs_shaders);
  size_t ofs_triangles = ofs_shaders + num_shaders * sizeof(md3Shader_t);
  md3_surf->ofsTriangles = LittleLong(ofs_triangles);
  size_t ofs_st = ofs_triangles + num_triangles * sizeof(md3Triangle_t);
  md3_surf->ofsSt = LittleLong(ofs_st);
  size_t ofs_xyznormals = ofs_st + num_verts * sizeof(md3St_t);
  md3_surf->ofsXyzNormals = LittleLong(ofs_xyznormals);
  size_t ofs_end = ofs_xyznormals + num_verts * sizeof(md3XyzNormal_t);
  md3_surf->ofsEnd = LittleLong(ofs_end);

  // Fill shader data.
  md3Shader_t* md3_shaders = (md3Shader_t*)((byte*)md3_surf + ofs_shaders);
  for (size_t i = 0; i < num_shaders; ++i) {
    model->get_surface_shader(model_data, surf_idx, i, MAX_QPATH,
                              md3_shaders[i].name);
    md3_shaders[i].shaderIndex = 0;
  }

  // Fill triangle data.
  md3Triangle_t* md3_triangles =
      (md3Triangle_t*)((byte*)md3_surf + ofs_triangles);
  for (size_t i = 0; i < num_triangles; ++i) {
    int triangle[3];
    model->get_surface_face(model_data, surf_idx, i, triangle);
    for (size_t j = 0; j < 3; ++j) {
      md3_triangles[i].indexes[j] = LittleLong(triangle[j]);
    }
  }

  // Fill texture coordinate data.
  md3St_t* md3_st = (md3St_t*)((byte*)md3_surf + ofs_st);
  for (size_t i = 0; i < num_verts; ++i) {
    float st[2];
    model->get_surface_vertex_st(model_data, surf_idx, i, st);
    for (size_t j = 0; j < 2; ++j) {
      md3_st[i].st[j] = LittleFloat(st[j]);
    }
  }

  // Fill vertex data.
  md3XyzNormal_t* md3_verts =
      (md3XyzNormal_t*)((byte*)md3_surf + ofs_xyznormals);
  for (size_t i = 0; i < num_verts; ++i) {
    float location[3];
    float normal[3];
    short md3_normal;

    // Fill vertex location.
    model->get_surface_vertex_location(model_data, surf_idx, i, location);
    for (size_t j = 0; j < 3; ++j) {
      md3_verts[i].xyz[j] = LittleShort(location[j] / MD3_XYZ_SCALE);
    }

    // Fill vertex normal.
    model->get_surface_vertex_normal(model_data, surf_idx, i, normal);
    NormalToLatLong(normal, (byte *)&md3_normal);
    md3_verts[i].normal = LittleShort(md3_normal);

    // Update bounding box.
    AABBExtendByPoint(bbox, location);
  }
}