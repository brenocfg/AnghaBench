#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  secret; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 TYPE_1__* get_user_f (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 

int set_user_secret (int user_id, const char *secret) {
  user_t *U = get_user_f (user_id);
  if (!U) {
    return 0;
  }

  if (!secret) {
    memset (U->secret, 0, 8);
    return 1;
  }

  if (strlen (secret) != 8) {
    return 0;
  }

  memcpy (U->secret, secret, 8);
  return 8;
}