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
struct TYPE_5__ {void** origin; void*** axis; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ md3Tag_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_tag_origin ) (void*,size_t,float*) ;int /*<<< orphan*/  (* get_tag_axis ) (void*,size_t,size_t,float*) ;int /*<<< orphan*/  (* get_tag_name ) (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ DeepmindModelGetters ;

/* Variables and functions */
 void* LittleFloat (float) ; 
 int /*<<< orphan*/  MAX_QPATH ; 
 int /*<<< orphan*/  stub1 (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (void*,size_t,size_t,float*) ; 
 int /*<<< orphan*/  stub3 (void*,size_t,float*) ; 

__attribute__((used)) static void SerialiseTag(               //
    size_t tag_idx,                     //
    const DeepmindModelGetters* model,  //
    void* model_data,                   //
    md3Tag_t* tag) {
  model->get_tag_name(model_data, tag_idx, MAX_QPATH, tag->name);
  for (size_t i = 0; i < 3; ++i) {
    float axis[3];
    model->get_tag_axis(model_data, tag_idx, i, axis);
    for (size_t j = 0; j < 3; ++j) {
      tag->axis[i][j] = LittleFloat(axis[j]);
    }
  }
  float origin[3];
  model->get_tag_origin(model_data, tag_idx, origin);
  for (size_t j = 0; j < 3; ++j) {
    tag->origin[j] = LittleFloat(origin[j]);
  }
}