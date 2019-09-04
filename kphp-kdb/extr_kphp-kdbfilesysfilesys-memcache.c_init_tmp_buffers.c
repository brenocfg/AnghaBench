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
struct connection {int /*<<< orphan*/  Tmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_head_buffer () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_tmp_buffers (struct connection*) ; 

__attribute__((used)) static inline void init_tmp_buffers (struct connection *c) {
  free_tmp_buffers (c);
  c->Tmp = alloc_head_buffer ();
  assert (c->Tmp);
}