#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct in_addr {void* s_addr; } ;
struct TYPE_2__ {int pos; scalar_t__ srcitem; scalar_t__ nItems; scalar_t__ lstart; struct in_addr ip; int /*<<< orphan*/ * srcptr; } ;
struct iplist {TYPE_1__ cur; } ;

/* Variables and functions */
 void* INADDR_ANY ; 
 void* htonl (scalar_t__) ; 
 int /*<<< orphan*/  iplist_nextrange (struct iplist*) ; 

struct in_addr
iplist_next(struct iplist *list)
{
  if (list->cur.pos == -1) {
    list->cur.srcptr = NULL;
    if (!iplist_nextrange(list)) {
      list->cur.ip.s_addr = INADDR_ANY;
      return list->cur.ip;
    }
  } else if (++list->cur.srcitem == list->cur.nItems) {
    if (!iplist_nextrange(list)) {
      list->cur.ip.s_addr = INADDR_ANY;
      list->cur.pos = -1;
      return list->cur.ip;
    }
  } else
    list->cur.ip.s_addr = htonl(list->cur.lstart + list->cur.srcitem);
  list->cur.pos++;

  return list->cur.ip;
}