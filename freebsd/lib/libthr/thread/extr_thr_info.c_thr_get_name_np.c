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
struct pthread {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
thr_get_name_np(struct pthread *thread, char *buf, size_t len)
{

	if (thread->name != NULL)
		strlcpy(buf, thread->name, len);
	else if (len > 0)
		buf[0] = '\0';
}