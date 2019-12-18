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
struct private_b64encode {int mode; int /*<<< orphan*/  name; } ;
struct archive_write_filter {int /*<<< orphan*/  archive; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_strcpy (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ atol8 (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int
archive_filter_b64encode_options(struct archive_write_filter *f, const char *key,
    const char *value)
{
	struct private_b64encode *state = (struct private_b64encode *)f->data;

	if (strcmp(key, "mode") == 0) {
		if (value == NULL) {
			archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
			    "mode option requires octal digits");
			return (ARCHIVE_FAILED);
		}
		state->mode = (int)atol8(value, strlen(value)) & 0777;
		return (ARCHIVE_OK);
	} else if (strcmp(key, "name") == 0) {
		if (value == NULL) {
			archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
			    "name option requires a string");
			return (ARCHIVE_FAILED);
		}
		archive_strcpy(&state->name, value);
		return (ARCHIVE_OK);
	}

	/* Note: The "warn" return is just to inform the options
	 * supervisor that we didn't handle it.  It will generate
	 * a suitable error if no one used this option. */
	return (ARCHIVE_WARN);
}