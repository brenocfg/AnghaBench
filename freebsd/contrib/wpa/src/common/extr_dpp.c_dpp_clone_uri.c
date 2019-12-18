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
struct dpp_bootstrap_info {scalar_t__ uri; } ;

/* Variables and functions */
 scalar_t__ os_strdup (char const*) ; 

__attribute__((used)) static int dpp_clone_uri(struct dpp_bootstrap_info *bi, const char *uri)
{
	bi->uri = os_strdup(uri);
	return bi->uri ? 0 : -1;
}