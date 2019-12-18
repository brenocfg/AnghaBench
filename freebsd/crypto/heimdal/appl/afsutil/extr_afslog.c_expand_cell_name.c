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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char const* _PATH_ARLA_CELLSERVDB ; 
 char const* _PATH_ARLA_DEBIAN_CELLSERVDB ; 
 char const* _PATH_CELLSERVDB ; 
 char const* _PATH_OPENAFS_DEBIAN_CELLSERVDB ; 
 char* expand_one_file (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 

__attribute__((used)) static const char *
expand_cell_name(const char *cell)
{
    FILE *f;
    const char *c;
    const char **fn, *files[] = { _PATH_CELLSERVDB,
				  _PATH_ARLA_CELLSERVDB,
				  _PATH_OPENAFS_DEBIAN_CELLSERVDB,
				  _PATH_ARLA_DEBIAN_CELLSERVDB,
				  NULL };
    for(fn = files; *fn; fn++) {
	f = fopen(*fn, "r");
	if(f == NULL)
	    continue;
	c = expand_one_file(f, cell);
	fclose(f);
	if(c)
	    return c;
    }
    return cell;
}