#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  md3Tag_t ;
struct TYPE_13__ {size_t ofsEnd; } ;
typedef  TYPE_1__ md3Surface_t ;
struct TYPE_14__ {int ident; int version; int numFrames; int numTags; int numSurfaces; int ofsFrames; int ofsTags; int ofsSurfaces; int ofsEnd; int /*<<< orphan*/  name; scalar_t__ numSkins; scalar_t__ flags; } ;
typedef  TYPE_2__ md3Header_t ;
struct TYPE_15__ {int /*<<< orphan*/  name; void* radius; void** localOrigin; void*** bounds; } ;
typedef  TYPE_3__ md3Frame_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_16__ {scalar_t__ radius; scalar_t__* origin; scalar_t__* extents; } ;
typedef  TYPE_4__ aabb_t ;
struct TYPE_17__ {size_t (* get_tag_count ) (void*) ;size_t (* get_surface_count ) (void*) ;int /*<<< orphan*/  (* get_name ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ DeepmindModelGetters ;

/* Variables and functions */
 int /*<<< orphan*/  AABBClear (TYPE_4__*) ; 
 int /*<<< orphan*/  AABBUpdateRadius (TYPE_4__*) ; 
 void* LittleFloat (scalar_t__) ; 
 int LittleLong (size_t) ; 
 int /*<<< orphan*/  MAX_QPATH ; 
 size_t MD3_IDENT ; 
 size_t MD3_VERSION ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SerialiseSurface (size_t,TYPE_5__ const*,void*,TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  SerialiseTag (size_t,TYPE_5__ const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t stub2 (void*) ; 
 size_t stub3 (void*) ; 

void dmlab_serialise_model(             //
    const DeepmindModelGetters* model,  //
    void* model_data,                   //
    void* buffer) {
  // Fill model data.
  md3Header_t* md3_model = (md3Header_t*)buffer;
  md3_model->ident = LittleLong(MD3_IDENT);
  md3_model->version =LittleLong(MD3_VERSION);
  model->get_name(model_data, MAX_QPATH, md3_model->name);
  md3_model->flags = 0;
  md3_model->numFrames = LittleLong(1);
  size_t num_tags = model->get_tag_count(model_data);
  md3_model->numTags = LittleLong(num_tags);
  size_t num_surfs = model->get_surface_count(model_data);
  md3_model->numSurfaces = LittleLong(num_surfs);
  md3_model->numSkins = 0;
  size_t ofs_frames = sizeof(md3Header_t);
  md3_model->ofsFrames = LittleLong(ofs_frames);
  size_t ofs_tags = ofs_frames + sizeof(md3Frame_t);
  md3_model->ofsTags = LittleLong(ofs_tags);
  size_t ofs_surfs = ofs_tags + num_tags * sizeof(md3Tag_t);
  md3_model->ofsSurfaces = LittleLong(ofs_surfs);

  // Fill tags.
  md3Tag_t* md3_tags = (md3Tag_t*)(buffer + ofs_tags);
  for (size_t i = 0; i < num_tags; ++i) {
    SerialiseTag(i, model, model_data, md3_tags + i);
  }

  // Fill surfaces.
  aabb_t bbox;
  AABBClear(&bbox);
  md3Surface_t* md3_surf = (md3Surface_t*)(buffer + ofs_surfs);
  for (size_t i = 0; i < num_surfs; ++i) {
    SerialiseSurface(i, model, model_data, md3_surf, &bbox);
    md3_surf = (md3Surface_t*)((byte*)md3_surf + LittleLong(md3_surf->ofsEnd));
  }

  // Fill frame data.
  AABBUpdateRadius(&bbox);
  md3Frame_t* md3_frame = (md3Frame_t*)(buffer + ofs_frames);
  for (size_t j = 0; j < 3; ++j) {
    md3_frame->bounds[0][j] = LittleFloat(bbox.origin[j] - bbox.extents[j]);
    md3_frame->bounds[1][j] = LittleFloat(bbox.origin[j] + bbox.extents[j]);
    md3_frame->localOrigin[j] = LittleFloat(bbox.origin[j]);
  }
  md3_frame->radius = LittleFloat(bbox.radius);
  Q_strncpyz(md3_frame->name, md3_model->name, sizeof(md3_frame->name));

  // Complete model data.
  size_t ofs_end = (byte*)md3_surf - (byte*)buffer;
  md3_model->ofsEnd = LittleLong(ofs_end);
}