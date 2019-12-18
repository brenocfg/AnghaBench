#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct iplist {int nItems; } ;
struct in_addr {int dummy; } ;

/* Variables and functions */
 struct in_addr iplist_setcurpos (struct iplist*,int) ; 
 int /*<<< orphan*/  randinit () ; 
 int random () ; 

struct in_addr
iplist_setrandpos(struct iplist *list)
{
  randinit();
  return iplist_setcurpos(list, random() % list->nItems);
}