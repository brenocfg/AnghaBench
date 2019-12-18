#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  weights_vector_t ;
struct TYPE_3__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  insert_use (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ vectors ; 

__attribute__((used)) static void add_use_front (weights_vector_t *V) {
  insert_use (&vectors, V, vectors.next);
}