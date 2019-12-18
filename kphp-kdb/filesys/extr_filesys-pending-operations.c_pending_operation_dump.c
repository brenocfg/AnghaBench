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
struct pending_operation {int /*<<< orphan*/  newpath; int /*<<< orphan*/  oldpath; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pending_operation_dump (struct pending_operation *P) {
  kprintf ("type:%d, oldpath: %s, newpath: %s\n", P->type, P->oldpath, P->newpath);
}