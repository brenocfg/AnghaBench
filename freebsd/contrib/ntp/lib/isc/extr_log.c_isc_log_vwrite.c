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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  isc_logmodule_t ;
typedef  int /*<<< orphan*/  isc_logcategory_t ;
typedef  int /*<<< orphan*/  isc_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  isc_log_doit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void
isc_log_vwrite(isc_log_t *lctx, isc_logcategory_t *category,
	       isc_logmodule_t *module, int level,
	       const char *format, va_list args)
{
	/*
	 * Contract checking is done in isc_log_doit().
	 */
	isc_log_doit(lctx, category, module, level, ISC_FALSE,
		     NULL, 0, 0, format, args);
}