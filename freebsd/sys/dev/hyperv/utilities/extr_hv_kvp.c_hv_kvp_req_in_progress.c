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
struct TYPE_3__ {int req_in_progress; } ;
typedef  TYPE_1__ hv_kvp_sc ;

/* Variables and functions */

__attribute__((used)) static int
hv_kvp_req_in_progress(hv_kvp_sc *sc)
{

	return (sc->req_in_progress);
}