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
struct TYPE_5__ {int no; int /*<<< orphan*/ * list; } ;
struct TYPE_6__ {TYPE_1__ grps; } ;
struct TYPE_7__ {TYPE_2__ tt; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ tokenstr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AU_OFLAG_XML ; 
 int /*<<< orphan*/  close_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_delim (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_tok_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
print_newgroups_tok(FILE *fp, tokenstr_t *tok, char *del, int oflags)
{
	int i;

	print_tok_type(fp, tok->id, "group", oflags);
	for (i = 0; i < tok->tt.grps.no; i++) {
		if (oflags & AU_OFLAG_XML) {
			fprintf(fp, "<gid>");
			print_group(fp, tok->tt.grps.list[i], oflags);
			fprintf(fp, "</gid>");
			close_tag(fp, tok->id);
		} else {
			print_delim(fp, del);
			print_group(fp, tok->tt.grps.list[i], oflags);
		}
	}
}