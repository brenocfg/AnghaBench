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
struct TYPE_3__ {unsigned int size; struct pollfd* items; } ;
typedef  TYPE_1__ uv__os390_epoll ;
struct pollfd {int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 unsigned int next_power_of_two (unsigned int) ; 
 struct pollfd* uv__realloc (struct pollfd*,unsigned int) ; 

__attribute__((used)) static void maybe_resize(uv__os390_epoll* lst, unsigned int len) {
  unsigned int newsize;
  unsigned int i;
  struct pollfd* newlst;
  struct pollfd event;

  if (len <= lst->size)
    return;

  if (lst->size == 0)
    event.fd = -1;
  else {
    /* Extract the message queue at the end. */
    event = lst->items[lst->size - 1];
    lst->items[lst->size - 1].fd = -1;
  }

  newsize = next_power_of_two(len);
  newlst = uv__realloc(lst->items, newsize * sizeof(lst->items[0]));

  if (newlst == NULL)
    abort();
  for (i = lst->size; i < newsize; ++i)
    newlst[i].fd = -1;

  /* Restore the message queue at the end */
  newlst[newsize - 1] = event;

  lst->items = newlst;
  lst->size = newsize;
}