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
typedef  scalar_t__ rating ;

/* Variables and functions */
 scalar_t__* ratings ; 

inline void rating_incr (const int a, rating cnt) {
#ifdef FADING
  rating dt = ((rating)(now - ratingT)) / RATING_NORM;
  ratings[a] += expf (dt) * cnt;
#else
  ratings[a] += cnt;
  if (ratings[a] < 0) {
    ratings[a] = 0;
  }
#endif
}