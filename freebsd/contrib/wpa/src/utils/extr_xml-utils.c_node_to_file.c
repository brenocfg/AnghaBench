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
typedef  int /*<<< orphan*/  xml_node_t ;
struct xml_node_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* xml_node_to_str (struct xml_node_ctx*,int /*<<< orphan*/ *) ; 

int node_to_file(struct xml_node_ctx *ctx, const char *fname, xml_node_t *node)
{
	FILE *f;
	char *str;

	str = xml_node_to_str(ctx, node);
	if (str == NULL)
		return -1;

	f = fopen(fname, "w");
	if (!f) {
		os_free(str);
		return -1;
	}

	fprintf(f, "%s\n", str);
	os_free(str);
	fclose(f);

	return 0;
}