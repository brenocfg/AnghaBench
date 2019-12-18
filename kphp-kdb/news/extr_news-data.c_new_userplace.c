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
typedef  int /*<<< orphan*/  userplace_t ;

/* Variables and functions */
 int /*<<< orphan*/  NOTIFY_MODE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  userplace_kept ; 
 int /*<<< orphan*/ * zmalloc0 (int) ; 

__attribute__((used)) static userplace_t *new_userplace (void) {
  assert (NOTIFY_MODE);
  userplace_kept ++;
  return zmalloc0 (sizeof (userplace_t));
}