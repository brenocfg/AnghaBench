#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  jobject ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  int /*<<< orphan*/  IJKFF_Pipeline ;

/* Variables and functions */
 int /*<<< orphan*/  ffpipeline_get_surface_as_global_ref_l (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffpipeline_lock_surface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffpipeline_unlock_surface (int /*<<< orphan*/ *) ; 

jobject ffpipeline_get_surface_as_global_ref(JNIEnv *env, IJKFF_Pipeline* pipeline)
{
    ffpipeline_lock_surface(pipeline);
    jobject new_surface = ffpipeline_get_surface_as_global_ref_l(env, pipeline);
    ffpipeline_unlock_surface(pipeline);
    return new_surface;
}