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
struct subprocess_capability {unsigned int flag; scalar_t__ name; } ;
struct child_process {int /*<<< orphan*/ * argv; int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,char const*) ; 
 int error (char*) ; 
 scalar_t__ packet_flush_gently (int /*<<< orphan*/ ) ; 
 char* packet_read_line (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ packet_write_fmt_gently (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  skip_prefix (char*,char*,char const**) ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static int handshake_capabilities(struct child_process *process,
				  struct subprocess_capability *capabilities,
				  unsigned int *supported_capabilities)
{
	int i;
	char *line;

	for (i = 0; capabilities[i].name; i++) {
		if (packet_write_fmt_gently(process->in, "capability=%s\n",
					    capabilities[i].name))
			return error("Could not write requested capability");
	}
	if (packet_flush_gently(process->in))
		return error("Could not write flush packet");

	while ((line = packet_read_line(process->out, NULL))) {
		const char *p;
		if (!skip_prefix(line, "capability=", &p))
			continue;

		for (i = 0;
		     capabilities[i].name && strcmp(p, capabilities[i].name);
		     i++)
			;
		if (capabilities[i].name) {
			if (supported_capabilities)
				*supported_capabilities |= capabilities[i].flag;
		} else {
			die("subprocess '%s' requested unsupported capability '%s'",
			    process->argv[0], p);
		}
	}

	return 0;
}