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
struct dl_list {int dummy; } ;
struct cli_txt_entry {int /*<<< orphan*/  list; int /*<<< orphan*/ * txt; } ;

/* Variables and functions */
 struct cli_txt_entry* cli_txt_list_get (struct dl_list*,char const*) ; 
 int /*<<< orphan*/  dl_list_add (struct dl_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct cli_txt_entry*) ; 
 int /*<<< orphan*/ * os_strdup (char const*) ; 
 struct cli_txt_entry* os_zalloc (int) ; 

int cli_txt_list_add(struct dl_list *txt_list, const char *txt)
{
	struct cli_txt_entry *e;

	e = cli_txt_list_get(txt_list, txt);
	if (e)
		return 0;
	e = os_zalloc(sizeof(*e));
	if (e == NULL)
		return -1;
	e->txt = os_strdup(txt);
	if (e->txt == NULL) {
		os_free(e);
		return -1;
	}
	dl_list_add(txt_list, &e->list);
	return 0;
}