#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* path; } ;
struct TYPE_4__ {TYPE_1__ dso; } ;
struct plugin {scalar_t__ type; TYPE_2__ u; struct plugin* next; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DSO ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ _krb5_expand_path_tokens (int /*<<< orphan*/ ,char*,char**) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,char*,...) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  is_valid_plugin_filename (char*) ; 
 int /*<<< orphan*/  krb5_config_free_strings (char**) ; 
 char** krb5_config_get_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  loadlib (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 scalar_t__ plugins_needs_scan ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 struct plugin* registered ; 
 char** rk_UNCONST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_cloexec_dir (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  sysplugin_dirs ; 
 int /*<<< orphan*/  trim_trailing_slash (char*) ; 

__attribute__((used)) static krb5_error_code
load_plugins(krb5_context context)
{
    struct plugin *e;
    krb5_error_code ret;
    char **dirs = NULL, **di;
    struct dirent *entry;
    char *path;
    DIR *d = NULL;

    if (!plugins_needs_scan)
	return 0;
    plugins_needs_scan = 0;

#ifdef HAVE_DLOPEN

    dirs = krb5_config_get_strings(context, NULL, "libdefaults",
				   "plugin_dir", NULL);
    if (dirs == NULL)
	dirs = rk_UNCONST(sysplugin_dirs);

    for (di = dirs; *di != NULL; di++) {
        char * dir = *di;

#ifdef KRB5_USE_PATH_TOKENS
        if (_krb5_expand_path_tokens(context, *di, &dir))
            goto next_dir;
#endif

        trim_trailing_slash(dir);

        d = opendir(dir);

	if (d == NULL)
	    goto next_dir;

	rk_cloexec_dir(d);

	while ((entry = readdir(d)) != NULL) {
	    char *n = entry->d_name;

	    /* skip . and .. */
            if (!is_valid_plugin_filename(n))
		continue;

	    path = NULL;
	    ret = 0;
#ifdef __APPLE__
	    { /* support loading bundles on MacOS */
		size_t len = strlen(n);
		if (len > 7 && strcmp(&n[len - 7],  ".bundle") == 0)
		    ret = asprintf(&path, "%s/%s/Contents/MacOS/%.*s", dir, n, (int)(len - 7), n);
	    }
#endif
	    if (ret < 0 || path == NULL)
		ret = asprintf(&path, "%s/%s", dir, n);

	    if (ret < 0 || path == NULL) {
		ret = ENOMEM;
		krb5_set_error_message(context, ret, "malloc: out of memory");
		return ret;
	    }

	    /* check if already tried */
	    for (e = registered; e != NULL; e = e->next)
		if (e->type == DSO && strcmp(e->u.dso.path, path) == 0)
		    break;
	    if (e) {
		free(path);
	    } else {
		loadlib(context, path); /* store or frees path */
	    }
	}
	closedir(d);

    next_dir:
        if (dir != *di)
            free(dir);
    }
    if (dirs != rk_UNCONST(sysplugin_dirs))
	krb5_config_free_strings(dirs);
#endif /* HAVE_DLOPEN */
    return 0;
}