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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  word4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shift_rows(uint32_t state[4])
{
  uint32_t u, v, x, y;

  u = word4(byte(state[0], 0),
            byte(state[1], 1),
            byte(state[2], 2),
            byte(state[3], 3));

  v = word4(byte(state[1], 0),
            byte(state[2], 1),
            byte(state[3], 2),
            byte(state[0], 3));

  x = word4(byte(state[2], 0),
            byte(state[3], 1),
            byte(state[0], 2),
            byte(state[1], 3));

  y = word4(byte(state[3], 0),
            byte(state[0], 1),
            byte(state[1], 2),
            byte(state[2], 3));

  state[0] = u;
  state[1] = v;
  state[2] = x;
  state[3] = y;
}