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
struct udp_target_set {int state; struct udp_target* last; struct udp_target* S; } ;
struct udp_target {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct udp_target_set*) ; 
 int /*<<< orphan*/  udp_target_set_expand (struct udp_target_set*) ; 

struct udp_target *udp_target_set_choose_target (struct udp_target_set *ST) {
  assert (ST);
  switch (ST->state) {
  case 0:
    return 0;
  case 1:
    udp_target_set_expand (ST);
  case 2:
    return ST->S;
  case 3:
    return ST->last;
  default:
    assert (0);
    return 0;
  }
}