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
typedef  int /*<<< orphan*/  user_t ;
typedef  int /*<<< orphan*/  recommend_user_t ;
typedef  int /*<<< orphan*/  notify_user_t ;

/* Variables and functions */
 scalar_t__ NOTIFY_MODE ; 
 int /*<<< orphan*/  RECOMMEND_MODE ; 
 scalar_t__ UG_MODE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void free_user_struct (user_t *U) {
  if (UG_MODE) {
    zfree (U, sizeof (user_t));
  } else if (NOTIFY_MODE) {
    zfree (U, sizeof (notify_user_t));
  } else {
    assert (RECOMMEND_MODE);
    zfree (U, sizeof (recommend_user_t));
  }
}