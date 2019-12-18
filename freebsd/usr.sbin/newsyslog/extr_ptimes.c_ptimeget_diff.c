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
 double difftime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

double
ptimeget_diff(const struct ptime_data *minuend, const struct
    ptime_data *subtrahend)
{

	/* Just like difftime(), we have no good error-return */
	if (minuend == NULL || subtrahend == NULL)
		return (0.0);

	return (difftime(minuend->tsecs, subtrahend->tsecs));
}