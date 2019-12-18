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
 int /*<<< orphan*/  repository_format_partial_clone ; 
 int /*<<< orphan*/  xstrdup_or_null (char*) ; 

void set_repository_format_partial_clone(char *partial_clone)
{
	repository_format_partial_clone = xstrdup_or_null(partial_clone);
}