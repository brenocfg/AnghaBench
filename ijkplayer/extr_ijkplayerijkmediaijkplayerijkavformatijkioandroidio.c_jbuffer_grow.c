#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jobject ;
struct TYPE_5__ {int jbuffer_capacity; int /*<<< orphan*/ * jbuffer; } ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  TYPE_1__ IjkURLContext ;
typedef  TYPE_2__ IjkIOAndroidioContext ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int /*<<< orphan*/  J4A_DeleteGlobalRef__p (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ J4A_ExceptionCheck__catchAll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * J4A_NewByteArray__asGlobalRef__catchAll (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static jobject jbuffer_grow(JNIEnv *env, IjkURLContext *h, int new_capacity) {
    IjkIOAndroidioContext *c = h->priv_data;
    if (!c)
        return NULL;

    if (c->jbuffer && c->jbuffer_capacity >= new_capacity)
        return c->jbuffer;

    new_capacity = FFMAX(new_capacity, c->jbuffer_capacity * 2);

    J4A_DeleteGlobalRef__p(env, &c->jbuffer);
    c->jbuffer_capacity = 0;

    c->jbuffer = J4A_NewByteArray__asGlobalRef__catchAll(env, new_capacity);
    if (J4A_ExceptionCheck__catchAll(env) || !c->jbuffer) {
        c->jbuffer = NULL;
        return NULL;
    }

    c->jbuffer_capacity = new_capacity;
    return c->jbuffer;
}