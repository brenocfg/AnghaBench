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
struct diffstat_file {int /*<<< orphan*/  print_name; int /*<<< orphan*/  comments; int /*<<< orphan*/  name; int /*<<< orphan*/  from_name; scalar_t__ is_renamed; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  pprint_rename (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quote_c_style (int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fill_print_name(struct diffstat_file *file)
{
	struct strbuf pname = STRBUF_INIT;

	if (file->print_name)
		return;

	if (file->is_renamed)
		pprint_rename(&pname, file->from_name, file->name);
	else
		quote_c_style(file->name, &pname, NULL, 0);

	if (file->comments)
		strbuf_addf(&pname, " (%s)", file->comments);

	file->print_name = strbuf_detach(&pname, NULL);
}