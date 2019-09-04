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
struct index_state {int dummy; } ;
struct attr_stack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  handle_attr_line (struct attr_stack*,char*,char const*,int,int) ; 
 char* read_blob_data_from_index (struct index_state const*,char const*,int /*<<< orphan*/ *) ; 
 char* strchrnul (char*,char) ; 
 struct attr_stack* xcalloc (int,int) ; 

__attribute__((used)) static struct attr_stack *read_attr_from_index(const struct index_state *istate,
					       const char *path,
					       int macro_ok)
{
	struct attr_stack *res;
	char *buf, *sp;
	int lineno = 0;

	if (!istate)
		return NULL;

	buf = read_blob_data_from_index(istate, path, NULL);
	if (!buf)
		return NULL;

	res = xcalloc(1, sizeof(*res));
	for (sp = buf; *sp; ) {
		char *ep;
		int more;

		ep = strchrnul(sp, '\n');
		more = (*ep == '\n');
		*ep = '\0';
		handle_attr_line(res, sp, path, ++lineno, macro_ok);
		sp = ep + more;
	}
	free(buf);
	return res;
}