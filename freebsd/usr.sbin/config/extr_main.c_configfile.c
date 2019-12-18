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
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  KERNCONFTAG ; 
 int /*<<< orphan*/  PREFIX ; 
 int /*<<< orphan*/  SBUF_AUTOEXTEND ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfgfile_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfgfile_removeall () ; 
 int /*<<< orphan*/  configfile_dynamic (struct sbuf*) ; 
 int /*<<< orphan*/  configfile_filebased (struct sbuf*) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ filebased ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 char* kernconfstr ; 
 int /*<<< orphan*/  moveifchanged (char*,char*) ; 
 char* path (char*) ; 
 int /*<<< orphan*/  sbuf_clear (struct sbuf*) ; 
 char* sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 char* strstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
configfile(void)
{
	FILE *fo;
	struct sbuf *sb;
	char *p;

	/* Add main configuration file to the list of files to be included */
	cfgfile_add(PREFIX);
	p = path("config.c.new");
	fo = fopen(p, "w");
	if (!fo)
		err(2, "%s", p);
	sb = sbuf_new(NULL, NULL, 2048, SBUF_AUTOEXTEND);
	assert(sb != NULL);
	sbuf_clear(sb);
	if (filebased) {
		/* Is needed, can be used for backward compatibility. */
		configfile_filebased(sb);
	} else {
		configfile_dynamic(sb);
	}
	sbuf_finish(sb);
	/* 
	 * We print first part of the template, replace our tag with
	 * configuration files content and later continue writing our
	 * template.
	 */
	p = strstr(kernconfstr, KERNCONFTAG);
	if (p == NULL)
		errx(EXIT_FAILURE, "Something went terribly wrong!");
	*p = '\0';
	fprintf(fo, "%s", kernconfstr);
	fprintf(fo, "%s", sbuf_data(sb));
	p += strlen(KERNCONFTAG);
	fprintf(fo, "%s", p);
	sbuf_delete(sb);
	fclose(fo);
	moveifchanged(path("config.c.new"), path("config.c"));
	cfgfile_removeall();
}