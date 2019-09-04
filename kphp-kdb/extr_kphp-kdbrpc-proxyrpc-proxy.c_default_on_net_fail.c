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

/* Variables and functions */
 int /*<<< orphan*/  TL_ERROR_NO_CONNECTIONS ; 
 int /*<<< orphan*/  tl_fetch_set_error (char*,int /*<<< orphan*/ ) ; 

int default_on_net_fail (void **IP, void **Data) {
  tl_fetch_set_error ("Can not find working connection to target", TL_ERROR_NO_CONNECTIONS);
  return -1;
}