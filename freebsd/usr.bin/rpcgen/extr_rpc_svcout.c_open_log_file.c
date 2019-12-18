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

/* Variables and functions */
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  fout ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static void
open_log_file(const char *infile, const char *sp)
{
	char *s;

	s = strrchr(infile, '.');
	if (s)
		*s = '\0';
	f_print(fout, "%sopenlog(\"%s\", LOG_PID, LOG_DAEMON);\n", sp, infile);
	if (s)
		*s = '.';
}