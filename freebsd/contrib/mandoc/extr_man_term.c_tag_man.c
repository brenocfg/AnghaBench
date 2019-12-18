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
struct termp {int /*<<< orphan*/  line; } ;
struct roff_node {scalar_t__ type; char* string; } ;

/* Variables and functions */
#define  ESCAPE_FONT 134 
#define  ESCAPE_FONTBI 133 
#define  ESCAPE_FONTBOLD 132 
#define  ESCAPE_FONTITALIC 131 
#define  ESCAPE_FONTPREV 130 
#define  ESCAPE_FONTROMAN 129 
#define  ESCAPE_SPECIAL 128 
 int INT_MAX ; 
 scalar_t__ ROFFT_TEXT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  isalpha (unsigned char) ; 
 int /*<<< orphan*/  mandoc_escape (char const**,char const**,int*) ; 
 int /*<<< orphan*/  tag_put (char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tag_man(struct termp *p, struct roff_node *n)
{
	const char	*cp, *arg;
	int		 prio, sz;

	assert(n->type == ROFFT_TEXT);
	cp = n->string;
	prio = 1;
	for (;;) {
		switch (*cp) {
		case ' ':
		case '\t':
			prio = INT_MAX;
			/* FALLTHROUGH */
		case '-':
			cp++;
			break;
		case '\\':
			cp++;
			switch (mandoc_escape(&cp, &arg, &sz)) {
			case ESCAPE_FONT:
			case ESCAPE_FONTROMAN:
			case ESCAPE_FONTITALIC:
			case ESCAPE_FONTBOLD:
			case ESCAPE_FONTPREV:
			case ESCAPE_FONTBI:
				break;
			case ESCAPE_SPECIAL:
				if (sz != 1)
					return;
				switch (*arg) {
				case '&':
				case '-':
				case 'e':
					break;
				default:
					return;
				}
				break;
			default:
				return;
			}
			break;
		default:
			if (isalpha((unsigned char)*cp))
				tag_put(cp, prio, p->line);
			return;
		}
	}
}