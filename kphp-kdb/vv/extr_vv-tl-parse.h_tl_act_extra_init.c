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
struct tl_act_extra {int size; int (* act ) (struct tl_act_extra*) ;scalar_t__ dup; scalar_t__ free; scalar_t__ flags; } ;

/* Variables and functions */

__attribute__((used)) static inline struct tl_act_extra *tl_act_extra_init (void *buf, int size, int (*act)(struct tl_act_extra *)) {
  struct tl_act_extra *extra = (struct tl_act_extra *)buf;
  extra->size = size + sizeof (*extra);
  extra->flags = 0;
  extra->act = act;
  extra->free = 0;
  extra->dup = 0;
  return extra;
}