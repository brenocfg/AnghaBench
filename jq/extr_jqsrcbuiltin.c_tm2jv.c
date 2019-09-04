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
struct tm {scalar_t__ tm_yday; scalar_t__ tm_wday; scalar_t__ tm_sec; scalar_t__ tm_min; scalar_t__ tm_hour; scalar_t__ tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int /*<<< orphan*/  JV_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_number (scalar_t__) ; 

__attribute__((used)) static jv tm2jv(struct tm *tm) {
  return JV_ARRAY(jv_number(tm->tm_year + 1900),
                  jv_number(tm->tm_mon),
                  jv_number(tm->tm_mday),
                  jv_number(tm->tm_hour),
                  jv_number(tm->tm_min),
                  jv_number(tm->tm_sec),
                  jv_number(tm->tm_wday),
                  jv_number(tm->tm_yday));
}