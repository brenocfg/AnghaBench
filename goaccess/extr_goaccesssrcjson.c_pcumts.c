#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  serve_usecs; } ;
struct TYPE_5__ {int /*<<< orphan*/  nts; } ;
struct TYPE_6__ {TYPE_1__ cumts; } ;
typedef  TYPE_2__ GMetrics ;
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 TYPE_4__ conf ; 
 int /*<<< orphan*/  pskeyu64val (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pcumts (GJSON * json, GMetrics * nmetrics, int sp)
{
  if (!conf.serve_usecs)
    return;
  pskeyu64val (json, "cumts", nmetrics->cumts.nts, sp, 0);
}