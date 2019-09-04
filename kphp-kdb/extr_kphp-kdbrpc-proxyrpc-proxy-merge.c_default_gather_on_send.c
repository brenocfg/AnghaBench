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
struct gather {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tl_copy_through (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_fetch_unread () ; 

int default_gather_on_send (struct gather *G, int num) {
  tl_copy_through (tl_fetch_unread (), 0);
  return 0;
}