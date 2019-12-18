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
struct cyclic_views_entry {int user_id; int /*<<< orphan*/  ad_id; } ;

/* Variables and functions */
 struct cyclic_views_entry* CV_r ; 
 struct cyclic_views_entry* CV_w ; 
 struct cyclic_views_entry* CViews ; 
 int CYCLIC_VIEWS_BUFFER_SIZE ; 
 int MAX_USERS ; 
 scalar_t__ R ; 
 int /*<<< orphan*/  assert (int) ; 
 int postprocess_recent_list (int) ; 

int compute_recent_user_ads (int user_id) {
  assert (CYCLIC_VIEWS_BUFFER_SIZE <= MAX_USERS / 2);
  struct cyclic_views_entry *from;
  long long *dest = (long long *) R;

  if (CV_r > CV_w) {
    for (from = CV_r; from < CViews + CYCLIC_VIEWS_BUFFER_SIZE; from++) {
      if (from->user_id == user_id) { 
	*dest++ = from->ad_id;
      }
    }
    for (from = CViews; from < CV_w; from++) {
      if (from->user_id == user_id) { 
	*dest++ = from->ad_id;
      }
    }
  } else {
    for (from = CV_r; from < CV_w; from++) {
      if (from->user_id == user_id) { 
	*dest++ = from->ad_id;
      }
    }
  }
  int cnt = dest - (long long *)R;
  return postprocess_recent_list (cnt);
}