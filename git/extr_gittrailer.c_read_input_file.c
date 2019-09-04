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

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strbuf_read (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strbuf_read_file (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_input_file(struct strbuf *sb, const char *file)
{
	if (file) {
		if (strbuf_read_file(sb, file, 0) < 0)
			die_errno(_("could not read input file '%s'"), file);
	} else {
		if (strbuf_read(sb, fileno(stdin), 0) < 0)
			die_errno(_("could not read from stdin"));
	}
}