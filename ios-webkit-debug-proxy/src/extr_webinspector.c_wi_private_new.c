#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* wi_private_t ;
struct wi_private {int dummy; } ;
struct TYPE_5__ {void* partial; void* in; } ;

/* Variables and functions */
 void* cb_new () ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wi_private_free (TYPE_1__*) ; 

wi_private_t wi_private_new() {
  wi_private_t my = (wi_private_t)malloc(sizeof(
        struct wi_private));
  if (my) {
    memset(my, 0, sizeof(struct wi_private));
    my->in = cb_new();
    my->partial = cb_new();
    if (!my->in || !my->partial) {
      wi_private_free(my);
      return NULL;
    }
  }
  return my;
}