#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* per_module_logging_file; } ;
struct TYPE_6__ {TYPE_1__ opt; } ;
struct TYPE_7__ {TYPE_2__ subn; } ;
typedef  TYPE_3__ osm_opensm_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* strerror (scalar_t__) ; 

__attribute__((used)) static void permodlog_parse(char **p_last, osm_opensm_t * p_osm, FILE * out)
{
	FILE *fp;
	char buf[1024];

	if (p_osm->subn.opt.per_module_logging_file != NULL) {
		fp = fopen(p_osm->subn.opt.per_module_logging_file, "r");
		if (!fp) {
			if (errno == ENOENT)
				return;
			fprintf(out, "fopen(%s) failed: %s\n",
				p_osm->subn.opt.per_module_logging_file,
				strerror(errno));
			return;
		}

		fprintf(out, "Per module logging file: %s\n",
			p_osm->subn.opt.per_module_logging_file);
		while (fgets(buf, sizeof buf, fp) != NULL)
			fprintf(out, "%s", buf);
		fclose(fp);
		fprintf(out, "\n");
	}
}