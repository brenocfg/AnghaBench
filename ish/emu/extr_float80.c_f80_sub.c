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
typedef  int /*<<< orphan*/  float80 ;

/* Variables and functions */
 int /*<<< orphan*/  f80_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f80_neg (int /*<<< orphan*/ ) ; 

float80 f80_sub(float80 a, float80 b) {
    return f80_add(a, f80_neg(b));
}