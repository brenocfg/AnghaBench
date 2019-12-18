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
struct tl_act_extra {int flags; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 struct tl_act_extra* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct tl_act_extra*,struct tl_act_extra*,int /*<<< orphan*/ ) ; 

struct tl_act_extra *tl_default_act_dup (struct tl_act_extra *extra) {
  struct tl_act_extra *new = malloc (extra->size);
  memcpy (new, extra, extra->size);
  new->flags = (new->flags & ~1) | 2;
  return new;
}