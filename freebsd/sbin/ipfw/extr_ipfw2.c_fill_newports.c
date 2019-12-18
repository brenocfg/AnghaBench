#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int len; } ;
struct TYPE_5__ {TYPE_1__ o; int /*<<< orphan*/ * ports; } ;
typedef  TYPE_2__ ipfw_insn_u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_LENGTH (int,int) ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int F_LEN_MASK ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strtoport (char*,char**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warnx (char*,char,char*) ; 

__attribute__((used)) static int
fill_newports(ipfw_insn_u16 *cmd, char *av, int proto, int cblen)
{
	uint16_t a, b, *p = cmd->ports;
	int i = 0;
	char *s = av;

	while (*s) {
		a = strtoport(av, &s, 0, proto);
		if (s == av) 			/* empty or invalid argument */
			return (0);

		CHECK_LENGTH(cblen, i + 2);

		switch (*s) {
		case '-':			/* a range */
			av = s + 1;
			b = strtoport(av, &s, 0, proto);
			/* Reject expressions like '1-abc' or '1-2-3'. */
			if (s == av || (*s != ',' && *s != '\0'))
				return (0);
			p[0] = a;
			p[1] = b;
			break;
		case ',':			/* comma separated list */
		case '\0':
			p[0] = p[1] = a;
			break;
		default:
			warnx("port list: invalid separator <%c> in <%s>",
				*s, av);
			return (0);
		}

		i++;
		p += 2;
		av = s + 1;
	}
	if (i > 0) {
		if (i + 1 > F_LEN_MASK)
			errx(EX_DATAERR, "too many ports/ranges\n");
		cmd->o.len |= i + 1;	/* leave F_NOT and F_OR untouched */
	}
	return (i);
}