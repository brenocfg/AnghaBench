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
struct blame_chain {struct blame* avail; } ;
struct blame {struct blame* next; } ;

/* Variables and functions */

__attribute__((used)) static void
blame_destroy(struct blame_chain *chain,
              struct blame *blame)
{
  blame->next = chain->avail;
  chain->avail = blame;
}