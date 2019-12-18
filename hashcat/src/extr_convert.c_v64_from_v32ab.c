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
struct TYPE_4__ {int /*<<< orphan*/  v64; TYPE_1__ v32; } ;
typedef  TYPE_2__ vconv64_t ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

u64 v64_from_v32ab (const u32 v32a, const u32 v32b)
{
  vconv64_t v;

  v.v32.a = v32a;
  v.v32.b = v32b;

  return v.v64;
}