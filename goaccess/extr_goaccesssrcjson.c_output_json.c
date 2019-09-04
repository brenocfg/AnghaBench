#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ json_pretty_print; } ;
struct TYPE_5__ {scalar_t__ size; char* buf; } ;
typedef  int /*<<< orphan*/  GLog ;
typedef  TYPE_1__ GJSON ;
typedef  int /*<<< orphan*/  GHolder ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 TYPE_4__ conf ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free_json (TYPE_1__*) ; 
 TYPE_1__* init_json_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nlines ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
output_json (GLog * glog, GHolder * holder, const char *filename)
{
  GJSON *json = NULL;
  FILE *fp;

  if (filename != NULL)
    fp = fopen (filename, "w");
  else
    fp = stdout;

  if (!fp)
    FATAL ("Unable to open JSON file: %s.", strerror (errno));

  /* use new lines to prettify output */
  if (conf.json_pretty_print)
    nlines = 1;

  /* spit it out */
  if ((json = init_json_output (glog, holder)) && json->size > 0) {
    fprintf (fp, "%s", json->buf);
    free_json (json);
  }

  fclose (fp);
}