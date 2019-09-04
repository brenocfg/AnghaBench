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
 char* strchr (char const*,char) ; 

__attribute__((used)) static const char *remove_ext_force(const char *url)
{
	if (url) {
		const char *colon = strchr(url, ':');
		if (colon && colon[1] == ':')
			return colon + 2;
	}
	return url;
}