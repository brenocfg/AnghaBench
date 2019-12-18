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
struct archive {struct archive_string_conv* sconv; } ;

/* Variables and functions */

__attribute__((used)) static void
add_sconv_object(struct archive *a, struct archive_string_conv *sc)
{
	struct archive_string_conv **psc; 

	/* Add a new sconv to sconv list. */
	psc = &(a->sconv);
	while (*psc != NULL)
		psc = &((*psc)->next);
	*psc = sc;
}