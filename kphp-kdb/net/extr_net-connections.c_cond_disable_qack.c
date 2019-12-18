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
struct connection {int flags; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int C_NOQACK ; 
 int /*<<< orphan*/  disable_qack (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cond_disable_qack (struct connection *c) {
  if (c->flags & C_NOQACK) {
    disable_qack (c->fd);
  }
}