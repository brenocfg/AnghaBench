#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct TYPE_4__ {int /*<<< orphan*/  v32; TYPE_1__ v16; } ;
typedef  TYPE_2__ vconv32_t ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */

u32 v32_from_v16ab (const u16 v16a, const u16 v16b)
{
  vconv32_t v;

  v.v16.a = v16a;
  v.v16.b = v16b;

  return v.v32;
}