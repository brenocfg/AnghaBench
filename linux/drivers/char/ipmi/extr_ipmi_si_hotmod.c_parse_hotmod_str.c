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
struct ipmi_plat_data {unsigned int type; unsigned int space; int /*<<< orphan*/  addr_source; int /*<<< orphan*/  slave_addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  regshift; int /*<<< orphan*/  regsize; int /*<<< orphan*/  regspacing; int /*<<< orphan*/  addr; int /*<<< orphan*/  iftype; } ;
typedef  enum hotmod_op { ____Placeholder_hotmod_op } hotmod_op ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPMI_PLAT_IF_SI ; 
 int /*<<< orphan*/  SI_HOTMOD ; 
 int check_hotmod_int_op (char const*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hotmod_as ; 
 int /*<<< orphan*/  hotmod_ops ; 
 int /*<<< orphan*/  hotmod_si ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int parse_str (int /*<<< orphan*/ ,unsigned int*,char*,char const**) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*,...) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int parse_hotmod_str(const char *curr, enum hotmod_op *op,
			    struct ipmi_plat_data *h)
{
	char *s, *o;
	int rv;
	unsigned int ival;

	h->iftype = IPMI_PLAT_IF_SI;
	rv = parse_str(hotmod_ops, &ival, "operation", &curr);
	if (rv)
		return rv;
	*op = ival;

	rv = parse_str(hotmod_si, &ival, "interface type", &curr);
	if (rv)
		return rv;
	h->type = ival;

	rv = parse_str(hotmod_as, &ival, "address space", &curr);
	if (rv)
		return rv;
	h->space = ival;

	s = strchr(curr, ',');
	if (s) {
		*s = '\0';
		s++;
	}
	rv = kstrtoul(curr, 0, &h->addr);
	if (rv) {
		pr_warn("Invalid hotmod address '%s': %d\n", curr, rv);
		return rv;
	}

	while (s) {
		curr = s;
		s = strchr(curr, ',');
		if (s) {
			*s = '\0';
			s++;
		}
		o = strchr(curr, '=');
		if (o) {
			*o = '\0';
			o++;
		}
		rv = check_hotmod_int_op(curr, o, "rsp", &h->regspacing);
		if (rv < 0)
			return rv;
		else if (rv)
			continue;
		rv = check_hotmod_int_op(curr, o, "rsi", &h->regsize);
		if (rv < 0)
			return rv;
		else if (rv)
			continue;
		rv = check_hotmod_int_op(curr, o, "rsh", &h->regshift);
		if (rv < 0)
			return rv;
		else if (rv)
			continue;
		rv = check_hotmod_int_op(curr, o, "irq", &h->irq);
		if (rv < 0)
			return rv;
		else if (rv)
			continue;
		rv = check_hotmod_int_op(curr, o, "ipmb", &h->slave_addr);
		if (rv < 0)
			return rv;
		else if (rv)
			continue;

		pr_warn("Invalid hotmod option '%s'\n", curr);
		return -EINVAL;
	}

	h->addr_source = SI_HOTMOD;
	return 0;
}