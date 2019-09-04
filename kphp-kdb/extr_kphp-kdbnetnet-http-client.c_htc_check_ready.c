#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct connection {int dummy; } ;
struct TYPE_2__ {int (* htc_check_ready ) (struct connection*) ;} ;

/* Variables and functions */
 TYPE_1__* HTC_FUNC (struct connection*) ; 
 int stub1 (struct connection*) ; 

int htc_check_ready (struct connection *c) {
  return HTC_FUNC(c)->htc_check_ready (c);
}