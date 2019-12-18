#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  string; } ;
struct value {int type; TYPE_1__ u; } ;
struct number {int dummy; } ;
typedef  enum bcode_compare { ____Placeholder_bcode_compare } bcode_compare ;
struct TYPE_4__ {int /*<<< orphan*/ * reg; } ;

/* Variables and functions */
#define  BCODE_NONE 130 
#define  BCODE_NUMBER 129 
#define  BCODE_STRING 128 
 int NO_ELSE ; 
 TYPE_2__ bmachine ; 
 int /*<<< orphan*/  bstrdup (int /*<<< orphan*/ ) ; 
 int compare_numbers (int,struct number*,struct number*) ; 
 int /*<<< orphan*/  eval_string (int /*<<< orphan*/ ) ; 
 struct number* pop_number () ; 
 int /*<<< orphan*/  push_number (struct number*) ; 
 char readch () ; 
 int readreg () ; 
 struct value* stack_tos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unreadch () ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,int,int) ; 

__attribute__((used)) static void
compare(enum bcode_compare type)
{
	struct number *a, *b;
	struct value *v;
	int idx, elseidx;
	bool ok;

	elseidx = NO_ELSE;
	idx = readreg();
	if (readch() == 'e')
		elseidx = readreg();
	else
		unreadch();

	a = pop_number();
	if (a == NULL)
		return;
	b = pop_number();
	if (b == NULL) {
		push_number(a);
		return;
	}

	ok = compare_numbers(type, a, b);

	if (!ok && elseidx != NO_ELSE)
		idx = elseidx;

	if (idx >= 0 && (ok || (!ok && elseidx != NO_ELSE))) {
		v = stack_tos(&bmachine.reg[idx]);
		if (v == NULL)
			warnx("register '%c' (0%o) is empty", idx, idx);
		else {
			switch(v->type) {
			case BCODE_NONE:
				warnx("register '%c' (0%o) is empty", idx, idx);
				break;
			case BCODE_NUMBER:
				warn("eval called with non-string argument");
				break;
			case BCODE_STRING:
				eval_string(bstrdup(v->u.string));
				break;
			}
		}
	}
}