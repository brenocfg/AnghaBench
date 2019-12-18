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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct TYPE_2__ {int pos; long srcitem; struct in_addr ip; scalar_t__ nItems; scalar_t__ lstart; int /*<<< orphan*/ * srcptr; } ;
struct iplist {unsigned int nItems; TYPE_1__ cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int /*<<< orphan*/  iplist_nextrange (struct iplist*) ; 

struct in_addr
iplist_setcurpos(struct iplist *list, long pos)
{
  if (pos < 0 || (unsigned)pos >= list->nItems) {
    list->cur.pos = -1;
    list->cur.ip.s_addr = INADDR_ANY;
    return list->cur.ip;
  }

  list->cur.srcptr = NULL;
  list->cur.pos = 0;
  while (1) {
    iplist_nextrange(list);
    if (pos < (int)list->cur.nItems) {
      if (pos) {
        list->cur.srcitem = pos;
        list->cur.pos += pos;
        list->cur.ip.s_addr = htonl(list->cur.lstart + list->cur.srcitem);
      }
      break;
    }
    pos -= list->cur.nItems;
    list->cur.pos += list->cur.nItems;
  }

  return list->cur.ip;
}