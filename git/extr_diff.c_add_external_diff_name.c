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
struct repository {int dummy; } ;
struct diff_tempfile {int /*<<< orphan*/  mode; int /*<<< orphan*/  hex; int /*<<< orphan*/  name; } ;
struct diff_filespec {int dummy; } ;
struct argv_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_push (struct argv_array*,int /*<<< orphan*/ ) ; 
 struct diff_tempfile* prepare_temp_file (struct repository*,char const*,struct diff_filespec*) ; 

__attribute__((used)) static void add_external_diff_name(struct repository *r,
				   struct argv_array *argv,
				   const char *name,
				   struct diff_filespec *df)
{
	struct diff_tempfile *temp = prepare_temp_file(r, name, df);
	argv_array_push(argv, temp->name);
	argv_array_push(argv, temp->hex);
	argv_array_push(argv, temp->mode);
}