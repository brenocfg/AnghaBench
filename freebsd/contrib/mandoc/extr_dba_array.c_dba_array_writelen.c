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
struct dba_array {scalar_t__ ed; scalar_t__ eu; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  dba_int_write (scalar_t__) ; 
 int /*<<< orphan*/  dba_skip (int /*<<< orphan*/ ,scalar_t__) ; 

int32_t
dba_array_writelen(struct dba_array *array, int32_t nmemb)
{
	dba_int_write(array->eu - array->ed);
	return dba_skip(nmemb, array->eu - array->ed);
}