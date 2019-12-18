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

/* Variables and functions */
 int MAX_PEND_VIEWS ; 
 int* Views ; 
 int /*<<< orphan*/  flush_views (int) ; 

__attribute__((used)) static void incr_views (int ad_id, int views) {
  if ((Views[ad_id] += views) >= MAX_PEND_VIEWS) {
    flush_views (ad_id);
  }
}