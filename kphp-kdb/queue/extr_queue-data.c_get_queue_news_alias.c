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
typedef  int /*<<< orphan*/  ll ;

/* Variables and functions */
 int /*<<< orphan*/  IS_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_news_s (int /*<<< orphan*/ ) ; 
 int get_queue_alias (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int get_queue_news_alias (ll id, ll *res) {
  if (!IS_UID(id)) {
    return 0;
  }

  return get_queue_alias (get_news_s (id), res);
}