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
struct TYPE_3__ {scalar_t__ top; scalar_t__ right; scalar_t__ bottom; scalar_t__ left; } ;
typedef  TYPE_1__ gaps_t ;

/* Variables and functions */

__attribute__((used)) static bool has_outer_gaps(gaps_t gaps) {
    return gaps.top > 0 ||
           gaps.right > 0 ||
           gaps.bottom > 0 ||
           gaps.left > 0;
}