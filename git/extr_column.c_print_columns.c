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
struct string_list {int /*<<< orphan*/  nr; } ;
struct column_options {char* indent; char* nl; int padding; int width; } ;
typedef  int /*<<< orphan*/  nopts ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int) ; 
 unsigned int COL_AUTO ; 
#define  COL_COLUMN 130 
 unsigned int COL_ENABLE_MASK ; 
 int COL_LAYOUT (unsigned int) ; 
#define  COL_PLAIN 129 
#define  COL_ROW 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  column_active (unsigned int) ; 
 int /*<<< orphan*/  display_plain (struct string_list const*,char*,char*) ; 
 int /*<<< orphan*/  display_table (struct string_list const*,unsigned int,struct column_options*) ; 
 int /*<<< orphan*/  memset (struct column_options*,int /*<<< orphan*/ ,int) ; 
 int term_columns () ; 

void print_columns(const struct string_list *list, unsigned int colopts,
		   const struct column_options *opts)
{
	struct column_options nopts;

	if (!list->nr)
		return;
	assert((colopts & COL_ENABLE_MASK) != COL_AUTO);

	memset(&nopts, 0, sizeof(nopts));
	nopts.indent = opts && opts->indent ? opts->indent : "";
	nopts.nl = opts && opts->nl ? opts->nl : "\n";
	nopts.padding = opts ? opts->padding : 1;
	nopts.width = opts && opts->width ? opts->width : term_columns() - 1;
	if (!column_active(colopts)) {
		display_plain(list, "", "\n");
		return;
	}
	switch (COL_LAYOUT(colopts)) {
	case COL_PLAIN:
		display_plain(list, nopts.indent, nopts.nl);
		break;
	case COL_ROW:
	case COL_COLUMN:
		display_table(list, colopts, &nopts);
		break;
	default:
		BUG("invalid layout mode %d", COL_LAYOUT(colopts));
	}
}