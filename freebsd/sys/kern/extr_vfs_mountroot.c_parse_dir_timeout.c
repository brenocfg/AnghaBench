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
 int EINVAL ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int parse_token (char**,char**) ; 
 long root_mount_timeout ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_dir_timeout(char **conf)
{
	char *tok, *endtok;
	long secs;
	int error;

	error = parse_token(conf, &tok);
	if (error)
		return (error);

	secs = strtol(tok, &endtok, 0);
	error = (secs < 0 || *endtok != '\0') ? EINVAL : 0;
	if (!error)
		root_mount_timeout = secs;
	free(tok, M_TEMP);
	return (error);
}