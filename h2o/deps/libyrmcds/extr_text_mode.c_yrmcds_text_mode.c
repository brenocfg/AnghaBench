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
typedef  int /*<<< orphan*/  yrmcds_error ;
struct TYPE_3__ {scalar_t__ serial; int text_mode; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ yrmcds ;

/* Variables and functions */
 int /*<<< orphan*/  YRMCDS_BAD_ARGUMENT ; 
 int /*<<< orphan*/  YRMCDS_IN_BINARY ; 
 int /*<<< orphan*/  YRMCDS_OK ; 
 int /*<<< orphan*/  YRMCDS_SYSTEM_ERROR ; 
 int errno ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

yrmcds_error yrmcds_text_mode(yrmcds* c) {
    if( c == NULL )
        return YRMCDS_BAD_ARGUMENT;

#ifndef LIBYRMCDS_NO_INTERNAL_LOCK
    int e = pthread_mutex_lock(&c->lock);
    if( e != 0 ) {
        errno = e;
        return YRMCDS_SYSTEM_ERROR;
    }
#endif // ! LIBYRMCDS_NO_INTERNAL_LOCK

    yrmcds_error ret = YRMCDS_OK;
    if( c->serial != 0 ) {
        ret = YRMCDS_IN_BINARY;
        goto OUT;
    }

    c->text_mode = 1;

  OUT:
#ifndef LIBYRMCDS_NO_INTERNAL_LOCK
    pthread_mutex_unlock(&c->lock);
#endif
    return ret;
}