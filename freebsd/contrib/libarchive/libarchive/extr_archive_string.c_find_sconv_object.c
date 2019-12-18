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
struct archive_string_conv {int /*<<< orphan*/  to_charset; int /*<<< orphan*/  from_charset; struct archive_string_conv* next; } ;
struct archive {struct archive_string_conv* sconv; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct archive_string_conv *
find_sconv_object(struct archive *a, const char *fc, const char *tc)
{
	struct archive_string_conv *sc; 

	if (a == NULL)
		return (NULL);

	for (sc = a->sconv; sc != NULL; sc = sc->next) {
		if (strcmp(sc->from_charset, fc) == 0 &&
		    strcmp(sc->to_charset, tc) == 0)
			break;
	}
	return (sc);
}