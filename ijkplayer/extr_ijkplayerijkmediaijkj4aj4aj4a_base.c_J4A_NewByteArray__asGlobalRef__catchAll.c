#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsize ;
typedef  int /*<<< orphan*/ * jbyteArray ;
struct TYPE_7__ {int /*<<< orphan*/ * (* NewGlobalRef ) (TYPE_1__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* NewByteArray ) (TYPE_1__**,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  J4A_DeleteLocalRef__p (TYPE_1__**,int /*<<< orphan*/ **) ; 
 scalar_t__ J4A_ExceptionCheck__catchAll (TYPE_1__**) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (TYPE_1__**,int /*<<< orphan*/ *) ; 

jbyteArray J4A_NewByteArray__asGlobalRef__catchAll(JNIEnv *env, jsize capacity)
{
    jbyteArray local = (*env)->NewByteArray(env, capacity);
    if (J4A_ExceptionCheck__catchAll(env) || !local)
        return NULL;

    jbyteArray global = (*env)->NewGlobalRef(env, local);
    J4A_DeleteLocalRef__p(env, &local);
    return global;
}