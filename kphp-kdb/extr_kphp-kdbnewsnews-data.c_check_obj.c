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
 scalar_t__ COMM_MODE ; 
 scalar_t__ NOTIFY_MODE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ check_split (int) ; 

__attribute__((used)) static int check_obj (int type, int owner, int place) {
  assert (COMM_MODE || NOTIFY_MODE);
  if (COMM_MODE) {
    return (check_split (place) || check_split (owner)) && (type >= 20) && (type <= 24);
  } else {
    return (type >= 0) && (type <= 31);
  }
}