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
struct passwd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * authorized_principals_file; } ;

/* Variables and functions */
 char* expand_authorized_keys (int /*<<< orphan*/ *,struct passwd*) ; 
 TYPE_1__ options ; 

char *
authorized_principals_file(struct passwd *pw)
{
	if (options.authorized_principals_file == NULL)
		return NULL;
	return expand_authorized_keys(options.authorized_principals_file, pw);
}