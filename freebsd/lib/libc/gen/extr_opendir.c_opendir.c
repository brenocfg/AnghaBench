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
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int DTF_HIDEW ; 
 int DTF_NODUP ; 
 int /*<<< orphan*/ * __opendir2 (char const*,int) ; 

DIR *
opendir(const char *name)
{

	return (__opendir2(name, DTF_HIDEW|DTF_NODUP));
}