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
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int read_phyregister (struct cfg*,int,int) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_phyregister (struct cfg*,int,int,int) ; 

__attribute__((used)) static int
set_phyregister(struct cfg *cfg, char *arg)
{
	int phy, reg, val;
	char *c, *d;
	
	phy = strtol(arg, &c, 0);
	if (c==arg)
		return (1);
	if (*c != '.')
		return (1);
	d = c+1;
	reg = strtol(d, &c, 0);
	if (d == c)
		return (1);
	if (*c == '=') {
		val = strtoul(c+1, NULL, 0);
		write_phyregister(cfg, phy, reg, val);
	}
	printf("\treg %d.0x%02x=0x%04x\n", phy, reg, read_phyregister(cfg, phy, reg));
	return (0);
}