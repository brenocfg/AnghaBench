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
struct TYPE_2__ {void* lstart; int nItems; char* srcptr; scalar_t__ srcitem; struct in_addr ip; } ;
struct iplist {TYPE_1__ cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_inet_aton (char*,char*,struct in_addr*) ; 
 int /*<<< orphan*/  inet_aton (char*,struct in_addr*) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strpbrk (char*,char*) ; 

__attribute__((used)) static int
iplist_setrange(struct iplist *list, char *range)
{
  char *ptr, *to;

  if ((ptr = strpbrk(range, ",-")) == NULL) {
    if (!inet_aton(range, &list->cur.ip))
      return 0;
    list->cur.lstart = ntohl(list->cur.ip.s_addr);
    list->cur.nItems = 1;
  } else {
    if (!do_inet_aton(range, ptr, &list->cur.ip))
      return 0;
    if (*ptr == ',') {
      list->cur.lstart = ntohl(list->cur.ip.s_addr);
      list->cur.nItems = 1;
    } else {
      struct in_addr endip;

      to = ptr+1;
      if ((ptr = strpbrk(to, ",-")) == NULL)
        ptr = to + strlen(to);
      if (*to == '-')
        return 0;
      if (!do_inet_aton(to, ptr, &endip))
        return 0;
      list->cur.lstart = ntohl(list->cur.ip.s_addr);
      list->cur.nItems = ntohl(endip.s_addr) - list->cur.lstart + 1;
      if (list->cur.nItems < 1)
        return 0;
    }
  }
  list->cur.srcitem = 0;
  list->cur.srcptr = range;
  return 1;
}