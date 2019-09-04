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
 int /*<<< orphan*/  AHd_retarget ; 
 int /*<<< orphan*/  insert_queue_ad_before (struct advert*,struct advert*) ; 

inline void insert_retarget_ad_last (struct advert *A) {
  insert_queue_ad_before ((struct advert *)&AHd_retarget, A);
}