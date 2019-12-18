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
struct string_list_item {int /*<<< orphan*/  string; } ;
struct string_list {struct string_list_item* items; } ;
struct menu_stuff {int type; int nr; scalar_t__ stuff; } ;
struct menu_item {char const hotkey; int /*<<< orphan*/  title; } ;

/* Variables and functions */
#define  MENU_STUFF_TYPE_MENU_ITEM 129 
#define  MENU_STUFF_TYPE_STRING_LIST 128 
 int /*<<< orphan*/  die (char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int find_unique(const char *choice, struct menu_stuff *menu_stuff)
{
	struct menu_item *menu_item;
	struct string_list_item *string_list_item;
	int i, len, found = 0;

	len = strlen(choice);
	switch (menu_stuff->type) {
	default:
		die("Bad type of menu_stuff when parse choice");
	case MENU_STUFF_TYPE_MENU_ITEM:

		menu_item = (struct menu_item *)menu_stuff->stuff;
		for (i = 0; i < menu_stuff->nr; i++, menu_item++) {
			if (len == 1 && *choice == menu_item->hotkey) {
				found = i + 1;
				break;
			}
			if (!strncasecmp(choice, menu_item->title, len)) {
				if (found) {
					if (len == 1) {
						/* continue for hotkey matching */
						found = -1;
					} else {
						found = 0;
						break;
					}
				} else {
					found = i + 1;
				}
			}
		}
		break;
	case MENU_STUFF_TYPE_STRING_LIST:
		string_list_item = ((struct string_list *)menu_stuff->stuff)->items;
		for (i = 0; i < menu_stuff->nr; i++, string_list_item++) {
			if (!strncasecmp(choice, string_list_item->string, len)) {
				if (found) {
					found = 0;
					break;
				}
				found = i + 1;
			}
		}
		break;
	}
	return found;
}