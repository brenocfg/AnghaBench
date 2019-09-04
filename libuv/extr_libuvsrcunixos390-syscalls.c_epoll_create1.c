#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int size; int /*<<< orphan*/  member; TYPE_1__* items; int /*<<< orphan*/  msg_queue; } ;
typedef  TYPE_2__ uv__os390_epoll ;
struct TYPE_7__ {scalar_t__ revents; int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  QUEUE_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  epoll_init ; 
 int /*<<< orphan*/  global_epoll_lock ; 
 int /*<<< orphan*/  global_epoll_queue ; 
 int /*<<< orphan*/  init_message_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  maybe_resize (TYPE_2__*,int) ; 
 int /*<<< orphan*/  once ; 
 TYPE_2__* uv__malloc (int) ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uv__os390_epoll* epoll_create1(int flags) {
  uv__os390_epoll* lst;

  lst = uv__malloc(sizeof(*lst));
  if (lst != NULL) {
    /* initialize list */
    lst->size = 0;
    lst->items = NULL;
    init_message_queue(lst);
    maybe_resize(lst, 1);
    lst->items[lst->size - 1].fd = lst->msg_queue;
    lst->items[lst->size - 1].events = POLLIN;
    lst->items[lst->size - 1].revents = 0;
    uv_once(&once, epoll_init);
    uv_mutex_lock(&global_epoll_lock);
    QUEUE_INSERT_TAIL(&global_epoll_queue, &lst->member);
    uv_mutex_unlock(&global_epoll_lock);
  }

  return lst;
}