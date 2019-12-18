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
struct news_id {scalar_t__ type; scalar_t__ owner; int place; } ;

/* Variables and functions */

__attribute__((used)) static int news_id_compare (struct news_id id1, struct news_id id2) {
  if (id1.type != id2.type) { return id1.type - id2.type; }
  if (id1.owner != id2.owner) { return id1.owner - id2.owner; }
  return id1.place - id2.place;
}