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
struct passwd {int dummy; } ;
typedef  int /*<<< orphan*/  Options ;

/* Variables and functions */
 int process_config_line_depth (int /*<<< orphan*/ *,struct passwd*,char const*,char const*,char*,char const*,int,int*,int,int /*<<< orphan*/ ) ; 

int
process_config_line(Options *options, struct passwd *pw, const char *host,
    const char *original_host, char *line, const char *filename,
    int linenum, int *activep, int flags)
{
	return process_config_line_depth(options, pw, host, original_host,
	    line, filename, linenum, activep, flags, 0);
}