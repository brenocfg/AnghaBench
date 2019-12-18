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
typedef  scalar_t__ u_long ;
typedef  scalar_t__ u_int32 ;
typedef  scalar_t__ associd_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static associd_t
checkassocid(
	u_int32 value
	)
{
	associd_t	associd;
	u_long		ulvalue;

	associd = (associd_t)value;
	if (0 == associd || value != associd) {
		ulvalue = value;
		fprintf(stderr,
			"***Invalid association ID %lu specified\n",
			ulvalue);
		return 0;
	}

	return associd;
}