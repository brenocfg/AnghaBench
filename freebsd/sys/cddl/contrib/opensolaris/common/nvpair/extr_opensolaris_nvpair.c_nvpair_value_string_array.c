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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  nvpair_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_TYPE_STRING_ARRAY ; 
 int nvpair_value_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char***) ; 

int
nvpair_value_string_array(nvpair_t *nvp, char ***val, uint_t *nelem)
{
	return (nvpair_value_common(nvp, DATA_TYPE_STRING_ARRAY, nelem, val));
}