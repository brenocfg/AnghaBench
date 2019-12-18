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
struct news_gather_extra {int /*<<< orphan*/  user_mode; } ;

/* Variables and functions */

int news_use_preget_query (void *extra) {
  return !((struct news_gather_extra *)extra)->user_mode;
}