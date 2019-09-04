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
typedef  int /*<<< orphan*/  GLog ;
typedef  int /*<<< orphan*/  GHolder ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_json (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
print_json_data (FILE * fp, GLog * glog, GHolder * holder)
{
  char *json = NULL;

  if ((json = get_json (glog, holder, 1)) == NULL)
    return;

  fprintf (fp, "<script type='text/javascript'>");
  fprintf (fp, "var json_data=%s", json);
  fprintf (fp, "</script>");

  free (json);
}