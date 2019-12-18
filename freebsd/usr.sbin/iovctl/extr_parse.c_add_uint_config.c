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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  ucl_object_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  report_config_error (char const*,int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  ucl_object_toint_safe (int /*<<< orphan*/  const*,scalar_t__*) ; 

__attribute__((used)) static void
add_uint_config(const char *key, const ucl_object_t *obj, nvlist_t *config,
    const char *type, uint64_t max)
{
	int64_t val;
	uint64_t uval;

	/* I must use a signed type here as libucl doesn't provide unsigned. */
	if (!ucl_object_toint_safe(obj, &val))
		report_config_error(key, obj, type);

	if (val < 0)
		report_config_error(key, obj, type);

	uval = val;
	if (uval > max)
		report_config_error(key, obj, type);

	nvlist_add_number(config, key, uval);
}