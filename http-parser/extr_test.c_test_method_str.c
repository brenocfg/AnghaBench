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
 int HTTP_GET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  http_method_str (int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

void
test_method_str (void)
{
  assert(0 == strcmp("GET", http_method_str(HTTP_GET)));
  assert(0 == strcmp("<unknown>", http_method_str(1337)));
}