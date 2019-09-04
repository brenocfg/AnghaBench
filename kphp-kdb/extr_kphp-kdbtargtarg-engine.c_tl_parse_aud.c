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
 int /*<<< orphan*/  MAX_AD_AUD ; 
 int tl_fetch_int_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tl_parse_aud (void) {
  return tl_fetch_int_range (0, MAX_AD_AUD);
}