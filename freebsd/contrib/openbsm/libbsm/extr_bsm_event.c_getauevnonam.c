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
typedef  int /*<<< orphan*/  au_event_t ;

/* Variables and functions */
 int /*<<< orphan*/ * getauevnonam_r (int /*<<< orphan*/ *,char const*) ; 

au_event_t *
getauevnonam(const char *event_name)
{
	static au_event_t event;

	return (getauevnonam_r(&event, event_name));
}