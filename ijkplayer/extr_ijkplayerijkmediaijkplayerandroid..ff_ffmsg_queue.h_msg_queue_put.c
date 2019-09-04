#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ MessageQueue ;
typedef  int /*<<< orphan*/  AVMessage ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_LockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UnlockMutex (int /*<<< orphan*/ ) ; 
 int msg_queue_put_private (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) inline static int msg_queue_put(MessageQueue *q, AVMessage *msg)
{
    int ret;

    SDL_LockMutex(q->mutex);
    ret = msg_queue_put_private(q, msg);
    SDL_UnlockMutex(q->mutex);

    return ret;
}