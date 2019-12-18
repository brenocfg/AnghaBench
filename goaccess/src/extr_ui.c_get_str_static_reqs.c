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
 int /*<<< orphan*/  REQUESTS_STATIC ; 
 int /*<<< orphan*/  ht_get_size_datamap (int /*<<< orphan*/ ) ; 
 char* int2str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
get_str_static_reqs (void)
{
  return int2str (ht_get_size_datamap (REQUESTS_STATIC), 0);
}