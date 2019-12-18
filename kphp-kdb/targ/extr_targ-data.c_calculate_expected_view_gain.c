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
struct advert {double expected_gain; } ;

/* Variables and functions */

inline double calculate_expected_view_gain (struct advert *A, int user_ad_views, int user_id) {
  return A->expected_gain;
}