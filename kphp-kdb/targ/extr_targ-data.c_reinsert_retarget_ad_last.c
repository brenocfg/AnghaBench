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
struct advert {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  insert_retarget_ad_last (struct advert*) ; 
 int /*<<< orphan*/  remove_queue_ad (struct advert*) ; 

inline void reinsert_retarget_ad_last (struct advert *A) {
  remove_queue_ad (A);
  insert_retarget_ad_last (A);
}