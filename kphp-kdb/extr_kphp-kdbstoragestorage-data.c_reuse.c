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
typedef  int /*<<< orphan*/  metafile_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_use (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_use (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reuse (metafile_t *meta) {
  del_use (meta);
  add_use (meta);
}