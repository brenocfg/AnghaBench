#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct blame_origin {int /*<<< orphan*/  path; TYPE_2__* commit; struct blame_origin* previous; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write_name_quoted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void write_filename_info(struct blame_origin *suspect)
{
	if (suspect->previous) {
		struct blame_origin *prev = suspect->previous;
		printf("previous %s ", oid_to_hex(&prev->commit->object.oid));
		write_name_quoted(prev->path, stdout, '\n');
	}
	printf("filename ");
	write_name_quoted(suspect->path, stdout, '\n');
}