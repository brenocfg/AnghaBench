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
struct cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int read_register (struct cfg*,int) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_register (struct cfg*,int,int) ; 

__attribute__((used)) static int
set_register(struct cfg *cfg, char *arg)
{
	int a, v;
	char *c;
	
	a = strtol(arg, &c, 0);
	if (c==arg)
		return (1);
	if (*c == '=') {
		v = strtoul(c+1, NULL, 0);
		write_register(cfg, a, v);
	}
	printf("\treg 0x%04x=0x%08x\n", a, read_register(cfg, a));
	return (0);
}