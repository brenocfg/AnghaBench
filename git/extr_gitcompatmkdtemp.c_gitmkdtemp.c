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
 scalar_t__ mkdir (char*,int) ; 
 int /*<<< orphan*/ * mktemp (char*) ; 

char *gitmkdtemp(char *template)
{
	if (!*mktemp(template) || mkdir(template, 0700))
		return NULL;
	return template;
}