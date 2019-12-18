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
 int /*<<< orphan*/  CURL_GLOBAL_DEFAULT ; 
 int curl_global_init (int /*<<< orphan*/ ) ; 

int kurl_init(void) // required for SSL and win32 socket; NOT thread safe
{
	return curl_global_init(CURL_GLOBAL_DEFAULT);
}