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
struct ptime_data {int /*<<< orphan*/  tsecs; } ;

/* Variables and functions */
 char const* ctime (int /*<<< orphan*/ *) ; 

const char *
ptimeget_ctime(const struct ptime_data *ptime)
{

	if (ptime == NULL)
		return ("Null time in ptimeget_ctime()\n");

	return (ctime(&ptime->tsecs));
}