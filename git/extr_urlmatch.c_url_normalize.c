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
struct url_info {int dummy; } ;

/* Variables and functions */
 char* url_normalize_1 (char const*,struct url_info*,int /*<<< orphan*/ ) ; 

char *url_normalize(const char *url, struct url_info *out_info)
{
	return url_normalize_1(url, out_info, 0);
}