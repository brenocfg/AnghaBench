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
struct mod_depend {int dummy; } ;
struct linker_file {int dummy; } ;
typedef  struct linker_file* linker_file_t ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LINKER_UNLOAD_FORCE ; 
 int /*<<< orphan*/  M_LINKER ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kld_sx ; 
 char* linker_basename (char*) ; 
 int linker_file_add_dependency (struct linker_file*,struct linker_file*) ; 
 int /*<<< orphan*/  linker_file_unload (struct linker_file*,int /*<<< orphan*/ ) ; 
 scalar_t__ linker_find_file_by_name (char const*) ; 
 int linker_load_file (char*,struct linker_file**) ; 
 char* linker_search_kld (char const*) ; 
 char* linker_search_module (char const*,int /*<<< orphan*/ ,struct mod_depend const*) ; 
 int /*<<< orphan*/ * modlist_lookup2 (char const*,struct mod_depend const*) ; 
 int /*<<< orphan*/ * rootvnode ; 
 char* strdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
linker_load_module(const char *kldname, const char *modname,
    struct linker_file *parent, const struct mod_depend *verinfo,
    struct linker_file **lfpp)
{
	linker_file_t lfdep;
	const char *filename;
	char *pathname;
	int error;

	sx_assert(&kld_sx, SA_XLOCKED);
	if (modname == NULL) {
		/*
 		 * We have to load KLD
 		 */
		KASSERT(verinfo == NULL, ("linker_load_module: verinfo"
		    " is not NULL"));
		pathname = linker_search_kld(kldname);
	} else {
		if (modlist_lookup2(modname, verinfo) != NULL)
			return (EEXIST);
		if (kldname != NULL)
			pathname = strdup(kldname, M_LINKER);
		else if (rootvnode == NULL)
			pathname = NULL;
		else
			/*
			 * Need to find a KLD with required module
			 */
			pathname = linker_search_module(modname,
			    strlen(modname), verinfo);
	}
	if (pathname == NULL)
		return (ENOENT);

	/*
	 * Can't load more than one file with the same basename XXX:
	 * Actually it should be possible to have multiple KLDs with
	 * the same basename but different path because they can
	 * provide different versions of the same modules.
	 */
	filename = linker_basename(pathname);
	if (linker_find_file_by_name(filename))
		error = EEXIST;
	else do {
		error = linker_load_file(pathname, &lfdep);
		if (error)
			break;
		if (modname && verinfo &&
		    modlist_lookup2(modname, verinfo) == NULL) {
			linker_file_unload(lfdep, LINKER_UNLOAD_FORCE);
			error = ENOENT;
			break;
		}
		if (parent) {
			error = linker_file_add_dependency(parent, lfdep);
			if (error)
				break;
		}
		if (lfpp)
			*lfpp = lfdep;
	} while (0);
	free(pathname, M_LINKER);
	return (error);
}