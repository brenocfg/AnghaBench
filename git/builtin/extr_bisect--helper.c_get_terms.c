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
struct strbuf {int dummy; } ;
struct bisect_terms {void* term_good; void* term_bad; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_terms (struct bisect_terms*) ; 
 int /*<<< orphan*/  git_path_bisect_terms () ; 
 void* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int get_terms(struct bisect_terms *terms)
{
	struct strbuf str = STRBUF_INIT;
	FILE *fp = NULL;
	int res = 0;

	fp = fopen(git_path_bisect_terms(), "r");
	if (!fp) {
		res = -1;
		goto finish;
	}

	free_terms(terms);
	strbuf_getline_lf(&str, fp);
	terms->term_bad = strbuf_detach(&str, NULL);
	strbuf_getline_lf(&str, fp);
	terms->term_good = strbuf_detach(&str, NULL);

finish:
	if (fp)
		fclose(fp);
	strbuf_release(&str);
	return res;
}