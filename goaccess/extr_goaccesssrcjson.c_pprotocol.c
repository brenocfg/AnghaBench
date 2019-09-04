#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ append_protocol; } ;
struct TYPE_4__ {scalar_t__ protocol; } ;
typedef  TYPE_1__ GMetrics ;
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 TYPE_3__ conf ; 
 int /*<<< orphan*/  pskeysval (int /*<<< orphan*/ *,char*,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pprotocol (GJSON * json, GMetrics * nmetrics, int sp)
{
  /* request protocol */
  if (conf.append_protocol && nmetrics->protocol) {
    pskeysval (json, "protocol", nmetrics->protocol, sp, 0);
  }
}