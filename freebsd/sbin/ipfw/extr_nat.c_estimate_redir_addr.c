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
typedef  int u_int ;
struct nat44_cfg_spool {int dummy; } ;
struct nat44_cfg_redir {int dummy; } ;

/* Variables and functions */
 char* strchr (char*,char) ; 

__attribute__((used)) static int
estimate_redir_addr(int *ac, char ***av)
{
	size_t space = sizeof(struct nat44_cfg_redir);
	char *sep = **av;
	u_int c = 0;

	(void)ac;	/* UNUSED */
	while ((sep = strchr(sep, ',')) != NULL) {
		c++;
		sep++;
	}

	if (c > 0)
		c++;

	space += c * sizeof(struct nat44_cfg_spool);

	return (space);
}