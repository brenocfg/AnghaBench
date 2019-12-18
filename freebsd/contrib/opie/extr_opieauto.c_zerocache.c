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
struct cachedotp {struct cachedotp* next; } ;

/* Variables and functions */
 struct cachedotp* head ; 
 int /*<<< orphan*/  memset (struct cachedotp*,int /*<<< orphan*/ ,int) ; 

void zerocache(void)
{
  struct cachedotp *c = head, *c2;

  while(c) {
    c2 = c->next;
    memset(c, 0, sizeof(struct cachedotp));
    c = c2;
  };
}