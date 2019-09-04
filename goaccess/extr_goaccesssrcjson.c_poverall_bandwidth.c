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
struct TYPE_3__ {int /*<<< orphan*/  resp_size; } ;
typedef  TYPE_1__ GLog ;
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 int /*<<< orphan*/  OVERALL_BANDWIDTH ; 
 int /*<<< orphan*/  pskeyu64val (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
poverall_bandwidth (GJSON * json, GLog * glog, int sp)
{
  pskeyu64val (json, OVERALL_BANDWIDTH, glog->resp_size, sp, 0);
}