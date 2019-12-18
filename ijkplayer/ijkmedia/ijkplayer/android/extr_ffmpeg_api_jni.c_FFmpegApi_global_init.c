#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  clazz; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* RegisterNatives ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  IJK_FIND_JAVA_CLASS (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JNI_CLASS_FFMPEG_API ; 
 int /*<<< orphan*/  NELEM (int /*<<< orphan*/ ) ; 
 TYPE_3__ g_clazz ; 
 int /*<<< orphan*/  g_methods ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int FFmpegApi_global_init(JNIEnv *env)
{
    int ret = 0;

    IJK_FIND_JAVA_CLASS(env, g_clazz.clazz, JNI_CLASS_FFMPEG_API);
    (*env)->RegisterNatives(env, g_clazz.clazz, g_methods, NELEM(g_methods));

    return ret;
}