#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jint ;
struct TYPE_6__ {int /*<<< orphan*/  field_SDK_INT; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* GetStaticIntField ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 TYPE_3__ class_J4AC_android_os_Build__VERSION ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

jint J4AC_android_os_Build__VERSION__SDK_INT__get(JNIEnv *env)
{
    return (*env)->GetStaticIntField(env, class_J4AC_android_os_Build__VERSION.id, class_J4AC_android_os_Build__VERSION.field_SDK_INT);
}