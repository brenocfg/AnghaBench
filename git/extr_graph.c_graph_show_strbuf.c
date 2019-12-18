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
struct strbuf {char* buf; int len; } ;
struct git_graph {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  graph_show_oneline (struct git_graph*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void graph_show_strbuf(struct git_graph *graph,
			      FILE *file,
			      struct strbuf const *sb)
{
	char *p;

	/*
	 * Print the strbuf line by line,
	 * and display the graph info before each line but the first.
	 */
	p = sb->buf;
	while (p) {
		size_t len;
		char *next_p = strchr(p, '\n');
		if (next_p) {
			next_p++;
			len = next_p - p;
		} else {
			len = (sb->buf + sb->len) - p;
		}
		fwrite(p, sizeof(char), len, file);
		if (next_p && *next_p != '\0')
			graph_show_oneline(graph);
		p = next_p;
	}
}