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
struct blame {scalar_t__ start; struct blame* next; } ;
typedef  scalar_t__ apr_off_t ;

/* Variables and functions */

__attribute__((used)) static struct blame *
blame_find(struct blame *blame, apr_off_t off)
{
  struct blame *prev = NULL;
  while (blame)
    {
      if (blame->start > off) break;
      prev = blame;
      blame = blame->next;
    }
  return prev;
}