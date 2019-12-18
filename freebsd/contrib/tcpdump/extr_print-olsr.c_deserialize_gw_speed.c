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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int MAX_SMARTGW_SPEED ; 
 int UINT8_MAX ; 

__attribute__((used)) static uint32_t deserialize_gw_speed(uint8_t value) {
  uint32_t speed;
  uint32_t exp;

  if (!value) {
    return 0;
  }

  if (value == UINT8_MAX) {
    /* maximum value: also return maximum value */
    return MAX_SMARTGW_SPEED;
  }

  speed = (value >> 3) + 1;
  exp = value & 7;

  while (exp-- > 0) {
    speed *= 10;
  }
  return speed;
}