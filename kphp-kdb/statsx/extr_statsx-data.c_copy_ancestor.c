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
struct counter {scalar_t__ meta; int /*<<< orphan*/  timezone; } ;

/* Variables and functions */

__attribute__((used)) static void copy_ancestor (struct counter *dst, struct counter *src) {
  dst->timezone = src->timezone;
  dst->meta = src->meta;
  src->meta = 0;
  //dst->type = src->type;
}