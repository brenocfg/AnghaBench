#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iso9660 {int opt_support_joliet; int /*<<< orphan*/  opt_support_rockridge; } ;
struct archive_read {TYPE_1__* format; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
archive_read_format_iso9660_options(struct archive_read *a,
		const char *key, const char *val)
{
	struct iso9660 *iso9660;

	iso9660 = (struct iso9660 *)(a->format->data);

	if (strcmp(key, "joliet") == 0) {
		if (val == NULL || strcmp(val, "off") == 0 ||
				strcmp(val, "ignore") == 0 ||
				strcmp(val, "disable") == 0 ||
				strcmp(val, "0") == 0)
			iso9660->opt_support_joliet = 0;
		else
			iso9660->opt_support_joliet = 1;
		return (ARCHIVE_OK);
	}
	if (strcmp(key, "rockridge") == 0 ||
	    strcmp(key, "Rockridge") == 0) {
		iso9660->opt_support_rockridge = val != NULL;
		return (ARCHIVE_OK);
	}

	/* Note: The "warn" return is just to inform the options
	 * supervisor that we didn't handle it.  It will generate
	 * a suitable error if no one used this option. */
	return (ARCHIVE_WARN);
}