#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * origin; int /*<<< orphan*/ ** axis; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ md3Tag_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_tag_origin ) (void*,size_t,float*) ;int /*<<< orphan*/  (* set_tag_axis ) (void*,size_t,size_t,float*) ;int /*<<< orphan*/  (* set_tag_name ) (void*,size_t,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ DeepmindModelSetters ;

/* Variables and functions */
 float LittleFloat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (void*,size_t,size_t,float*) ; 
 int /*<<< orphan*/  stub3 (void*,size_t,float*) ; 

__attribute__((used)) static void DeserialiseTag(                     //
    const md3Tag_t* md3_tag,                    //
    size_t tag_idx,                             //
    const DeepmindModelSetters* model_setters,  //
    void* model_data) {
  model_setters->set_tag_name(model_data, tag_idx, md3_tag->name);
  for (size_t i = 0; i < 3; ++i) {
    float axis[3];
    for (size_t j = 0; j < 3; ++j) {
      axis[j] = LittleFloat(md3_tag->axis[i][j]);
    }
    model_setters->set_tag_axis(model_data, tag_idx, i, axis);
  }
  float origin[3];
  for (size_t j = 0; j < 3; ++j) {
    origin[j] = LittleFloat(md3_tag->origin[j]);
  }
  model_setters->set_tag_origin(model_data, tag_idx, origin);
}