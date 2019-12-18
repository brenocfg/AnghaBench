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
 char const ARGFLAG ; 
 int /*<<< orphan*/  COMMA ; 
 int /*<<< orphan*/  PUSHBACK (char const) ; 
 char const* lquote ; 
 int /*<<< orphan*/  pbnum (int) ; 
 int /*<<< orphan*/  pbstr (char const*) ; 
 int /*<<< orphan*/  pushback (int /*<<< orphan*/ ) ; 
 char const* rquote ; 

void
expand_macro(const char *argv[], int argc)
{
	const char *t;
	const char *p;
	int n;
	int argno;

	t = argv[0];		       /* defn string as a whole */
	p = t;
	while (*p)
		p++;
	p--;			       /* last character of defn */
	while (p > t) {
		if (*(p - 1) != ARGFLAG)
			PUSHBACK(*p);
		else {
			switch (*p) {

			case '#':
				pbnum(argc - 2);
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if ((argno = *p - '0') < argc - 1)
					pbstr(argv[argno + 1]);
				break;
			case '*':
				if (argc > 2) {
					for (n = argc - 1; n > 2; n--) {
						pbstr(argv[n]);
						pushback(COMMA);
					}
					pbstr(argv[2]);
				}
				break;
                        case '@':
				if (argc > 2) {
					for (n = argc - 1; n > 2; n--) {
						pbstr(rquote);
						pbstr(argv[n]);
						pbstr(lquote);
						pushback(COMMA);
					}
					pbstr(rquote);
					pbstr(argv[2]);
					pbstr(lquote);
				}
                                break;
			default:
				PUSHBACK(*p);
				PUSHBACK('$');
				break;
			}
			p--;
		}
		p--;
	}
	if (p == t)		       /* do last character */
		PUSHBACK(*p);
}