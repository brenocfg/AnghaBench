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
struct pax {int /*<<< orphan*/  l_url_encoded_name; int /*<<< orphan*/  sparse_map; int /*<<< orphan*/  pax_header; } ;
struct archive_write {int /*<<< orphan*/ * format_data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct pax*) ; 
 int /*<<< orphan*/  sparse_list_clear (struct pax*) ; 

__attribute__((used)) static int
archive_write_pax_free(struct archive_write *a)
{
	struct pax *pax;

	pax = (struct pax *)a->format_data;
	if (pax == NULL)
		return (ARCHIVE_OK);

	archive_string_free(&pax->pax_header);
	archive_string_free(&pax->sparse_map);
	archive_string_free(&pax->l_url_encoded_name);
	sparse_list_clear(pax);
	free(pax);
	a->format_data = NULL;
	return (ARCHIVE_OK);
}