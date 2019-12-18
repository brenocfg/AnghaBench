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
struct symbol {int flags; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct menu {struct menu* next; struct menu* parent; struct menu* list; struct symbol* sym; } ;
struct TYPE_2__ {struct menu* list; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_MAX ; 
 int SYMBOL_CHOICE ; 
 int SYMBOL_WRITE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  conf_get_changed () ; 
 char* conf_get_configname () ; 
 int /*<<< orphan*/  conf_message (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  conf_write_heading (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conf_write_symbol (int /*<<< orphan*/ *,struct symbol*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 char* getenv (char*) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  kconfig_printer_cb ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* menu_get_prompt (struct menu*) ; 
 int /*<<< orphan*/  menu_is_visible (struct menu*) ; 
 scalar_t__ rename (char*,char*) ; 
 TYPE_1__ rootmenu ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  sym_calc_value (struct symbol*) ; 
 int /*<<< orphan*/  sym_clear_all_valid () ; 
 int /*<<< orphan*/  sym_set_change_count (int /*<<< orphan*/ ) ; 

int conf_write(const char *name)
{
	FILE *out;
	struct symbol *sym;
	struct menu *menu;
	const char *basename;
	const char *str;
	char dirname[PATH_MAX+1], tmpname[PATH_MAX+1], newname[PATH_MAX+1];
	char *env;

	dirname[0] = 0;
	if (name && name[0]) {
		struct stat st;
		char *slash;

		if (!stat(name, &st) && S_ISDIR(st.st_mode)) {
			strcpy(dirname, name);
			strcat(dirname, "/");
			basename = conf_get_configname();
		} else if ((slash = strrchr(name, '/'))) {
			int size = slash - name + 1;
			memcpy(dirname, name, size);
			dirname[size] = 0;
			if (slash[1])
				basename = slash + 1;
			else
				basename = conf_get_configname();
		} else
			basename = name;
	} else
		basename = conf_get_configname();

	sprintf(newname, "%s%s", dirname, basename);
	env = getenv("KCONFIG_OVERWRITECONFIG");
	if (!env || !*env) {
		sprintf(tmpname, "%s.tmpconfig.%d", dirname, (int)getpid());
		out = fopen(tmpname, "w");
	} else {
		*tmpname = 0;
		out = fopen(newname, "w");
	}
	if (!out)
		return 1;

	conf_write_heading(out, &kconfig_printer_cb, NULL);

	if (!conf_get_changed())
		sym_clear_all_valid();

	menu = rootmenu.list;
	while (menu) {
		sym = menu->sym;
		if (!sym) {
			if (!menu_is_visible(menu))
				goto next;
			str = menu_get_prompt(menu);
			fprintf(out, "\n"
				     "#\n"
				     "# %s\n"
				     "#\n", str);
		} else if (!(sym->flags & SYMBOL_CHOICE)) {
			sym_calc_value(sym);
			if (!(sym->flags & SYMBOL_WRITE))
				goto next;
			sym->flags &= ~SYMBOL_WRITE;

			conf_write_symbol(out, sym, &kconfig_printer_cb, NULL);
		}

next:
		if (menu->list) {
			menu = menu->list;
			continue;
		}
		if (menu->next)
			menu = menu->next;
		else while ((menu = menu->parent)) {
			if (menu->next) {
				menu = menu->next;
				break;
			}
		}
	}
	fclose(out);

	if (*tmpname) {
		strcat(dirname, basename);
		strcat(dirname, ".old");
		rename(newname, dirname);
		if (rename(tmpname, newname))
			return 1;
	}

	conf_message(_("configuration written to %s"), newname);

	sym_set_change_count(0);

	return 0;
}