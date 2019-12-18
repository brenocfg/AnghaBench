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
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 int /*<<< orphan*/  block_bind_each (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  block_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static block block_bind(block binder, block body, int bindflags) {
  block_bind_each(binder, body, bindflags);
  return block_join(binder, body);
}