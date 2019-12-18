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
struct archive_string_conv {struct archive_string_conv* next; } ;
struct archive {int /*<<< orphan*/ * current_code; struct archive_string_conv* sconv; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_sconv_object (struct archive_string_conv*) ; 

void
archive_string_conversion_free(struct archive *a)
{
	struct archive_string_conv *sc; 
	struct archive_string_conv *sc_next; 

	for (sc = a->sconv; sc != NULL; sc = sc_next) {
		sc_next = sc->next;
		free_sconv_object(sc);
	}
	a->sconv = NULL;
	free(a->current_code);
	a->current_code = NULL;
}