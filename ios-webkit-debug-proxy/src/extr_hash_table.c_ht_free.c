#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ht_struct {int dummy; } ;
typedef  TYPE_1__* ht_t ;
struct TYPE_6__ {struct TYPE_6__* buckets; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  ht_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void ht_free(ht_t self) {
  if (self) {
    ht_clear(self);
    free(self->buckets);
    memset(self, 0, sizeof(struct ht_struct));
    free(self);
  }
}