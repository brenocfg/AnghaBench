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
struct cyclic_views_entry {int user_id; int /*<<< orphan*/  time; int /*<<< orphan*/  ad_id; } ;
struct advert {int /*<<< orphan*/  recent_views; int /*<<< orphan*/  ad_id; } ;

/* Variables and functions */
 struct cyclic_views_entry* CV_r ; 
 struct cyclic_views_entry* CV_w ; 
 struct cyclic_views_entry* CViews ; 
 int CYCLIC_VIEWS_BUFFER_SIZE ; 
 int /*<<< orphan*/  forget_old_views () ; 
 int /*<<< orphan*/  forget_one_view () ; 
 int /*<<< orphan*/  log_last_ts ; 

void register_one_view (struct advert *A, int user_id) {
  struct cyclic_views_entry *CV = CV_w;
  CV->ad_id = A->ad_id;
  CV->user_id = user_id;
  CV->time = log_last_ts;
  A->recent_views++;
  if (++CV_w == CViews + CYCLIC_VIEWS_BUFFER_SIZE) {
    CV_w = CViews;
  }
  if (CV_w == CV_r) {
    forget_one_view ();
  }
  forget_old_views ();
}