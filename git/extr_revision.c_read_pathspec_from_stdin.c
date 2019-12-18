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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct argv_array {int dummy; } ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_pathspec_from_stdin(struct strbuf *sb,
				     struct argv_array *prune)
{
	while (strbuf_getline(sb, stdin) != EOF)
		argv_array_push(prune, sb->buf);
}