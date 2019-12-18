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
typedef  int /*<<< orphan*/  ucl_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  ucl_object_tostring (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
report_config_error(const char *key, const ucl_object_t *obj, const char *type)
{

	errx(1, "Value '%s' of key '%s' is not of type %s",
	    ucl_object_tostring(obj), key, type);
}