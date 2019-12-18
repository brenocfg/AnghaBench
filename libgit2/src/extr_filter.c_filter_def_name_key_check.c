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
struct TYPE_2__ {char* filter_name; } ;
typedef  TYPE_1__ git_filter_def ;

/* Variables and functions */
 int git__strcmp (void const*,char const*) ; 

__attribute__((used)) static int filter_def_name_key_check(const void *key, const void *fdef)
{
	const char *name =
		fdef ? ((const git_filter_def *)fdef)->filter_name : NULL;
	return name ? git__strcmp(key, name) : -1;
}