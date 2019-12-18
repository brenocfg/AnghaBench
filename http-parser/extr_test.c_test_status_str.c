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
 int HTTP_STATUS_NOT_FOUND ; 
 int HTTP_STATUS_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  http_status_str (int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

void
test_status_str (void)
{
  assert(0 == strcmp("OK", http_status_str(HTTP_STATUS_OK)));
  assert(0 == strcmp("Not Found", http_status_str(HTTP_STATUS_NOT_FOUND)));
  assert(0 == strcmp("<unknown>", http_status_str(1337)));
}