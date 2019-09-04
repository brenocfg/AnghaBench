#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_28__ ;
typedef  struct TYPE_37__   TYPE_22__ ;
typedef  struct TYPE_36__   TYPE_1__ ;
typedef  struct TYPE_35__   TYPE_18__ ;
typedef  struct TYPE_34__   TYPE_12__ ;
typedef  struct TYPE_33__   TYPE_11__ ;
typedef  struct TYPE_32__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
typedef  TYPE_10__* Tree ;
struct TYPE_45__ {int label; } ;
struct TYPE_46__ {TYPE_8__ l; } ;
struct TYPE_43__ {int label; } ;
struct TYPE_44__ {TYPE_6__ f; } ;
struct TYPE_41__ {int label; } ;
struct TYPE_42__ {TYPE_4__ l; } ;
struct TYPE_39__ {int /*<<< orphan*/  i; int /*<<< orphan*/  u; } ;
struct TYPE_40__ {TYPE_2__ v; } ;
struct TYPE_38__ {TYPE_7__ u; int /*<<< orphan*/  type; } ;
struct TYPE_37__ {TYPE_5__ u; } ;
struct TYPE_36__ {int /*<<< orphan*/  type; } ;
struct TYPE_35__ {int /*<<< orphan*/  op; } ;
struct TYPE_34__ {int lab; TYPE_22__* deflab; TYPE_1__* sym; } ;
struct TYPE_33__ {TYPE_9__ u; int /*<<< orphan*/  src; int /*<<< orphan*/  scope; } ;
struct TYPE_32__ {TYPE_3__ u; TYPE_18__* type; int /*<<< orphan*/  op; } ;
typedef  TYPE_11__* Symbol ;
typedef  TYPE_12__* Swtch ;

/* Variables and functions */
 int Aflag ; 
#define  BREAK 139 
#define  CASE 138 
 int /*<<< orphan*/  CNST ; 
#define  CONTINUE 137 
#define  DEFAULT 136 
#define  DO 135 
 int EOI ; 
#define  FOR 134 
 int /*<<< orphan*/  FUNC ; 
#define  GOTO 133 
#define  ID 132 
#define  IF 131 
 int /*<<< orphan*/  LABELS ; 
#define  RETURN 130 
 int /*<<< orphan*/  STMT ; 
#define  SWITCH 129 
 int /*<<< orphan*/  UNSIGNED ; 
#define  WHILE 128 
 int /*<<< orphan*/  branch (int) ; 
 int /*<<< orphan*/  caselabel (TYPE_12__*,int /*<<< orphan*/ ,int) ; 
 TYPE_10__* cast (TYPE_10__*,int /*<<< orphan*/ ) ; 
 TYPE_28__* cfunc ; 
 int /*<<< orphan*/  compound (int,TYPE_12__*,int) ; 
 TYPE_10__* constexpr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  definelab (int) ; 
 int /*<<< orphan*/  definept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dostmt (void*,TYPE_12__*,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/ * expr (int /*<<< orphan*/ ) ; 
 TYPE_10__* expr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extend (int /*<<< orphan*/ ,TYPE_18__*) ; 
 TYPE_22__* findlabel (int) ; 
 int /*<<< orphan*/  forstmt (void*,TYPE_12__*,int) ; 
 int /*<<< orphan*/  freturn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic (int /*<<< orphan*/ ) ; 
 void* genlabel (int) ; 
 char getchr () ; 
 int gettok () ; 
 int /*<<< orphan*/  glevel ; 
 int /*<<< orphan*/  ifstmt (void*,int,TYPE_12__*,int) ; 
 TYPE_11__* install (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isint (TYPE_18__*) ; 
 int const* kind ; 
 int /*<<< orphan*/  listnodes (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_11__* lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  needconst ; 
 int nodecount ; 
 float refinc ; 
 int /*<<< orphan*/  retcode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skipto (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  src ; 
 int /*<<< orphan*/  stmtlabel () ; 
 int /*<<< orphan*/  stmtlabs ; 
 int /*<<< orphan*/  swstmt (int,void*,int) ; 
 int t ; 
 int /*<<< orphan*/  test (char,char*) ; 
 int /*<<< orphan*/  token ; 
 int /*<<< orphan*/  use (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  voidtype ; 
 int /*<<< orphan*/  walk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*) ; 
 int /*<<< orphan*/  whilestmt (void*,TYPE_12__*,int) ; 

void statement(int loop, Swtch swp, int lev) {
	float ref = refinc;

	if (Aflag >= 2 && lev == 15)
		warning("more than 15 levels of nested statements\n");
	switch (t) {
	case IF:       ifstmt(genlabel(2), loop, swp, lev + 1);
 break;
	case WHILE:    whilestmt(genlabel(3), swp, lev + 1); break;
	case DO:       dostmt(genlabel(3), swp, lev + 1); expect(';');
					break;

	case FOR:      forstmt(genlabel(4), swp, lev + 1);
 break;
	case BREAK:    walk(NULL, 0, 0);
		       definept(NULL);
		       if (swp && swp->lab > loop)
		       	branch(swp->lab + 1);
		       else if (loop)
		       	branch(loop + 2);
		       else
		       	error("illegal break statement\n");
		       t = gettok(); expect(';');
					   break;

	case CONTINUE: walk(NULL, 0, 0);
		       definept(NULL);
		       if (loop)
		       	branch(loop + 1);
		       else
		       	error("illegal continue statement\n");
		       t = gettok(); expect(';');
					      break;

	case SWITCH:   swstmt(loop, genlabel(2), lev + 1);
 break;
	case CASE:     {
		       	int lab = genlabel(1);
		       	if (swp == NULL)
		       		error("illegal case label\n");
		       	definelab(lab);
		       	while (t == CASE) {
		       		static char stop[] = { IF, ID, 0 };
		       		Tree p;
		       		t = gettok();
		       		p = constexpr(0);
		       		if (generic(p->op) == CNST && isint(p->type)) {
		       			if (swp) {
		       				needconst++;
		       				p = cast(p, swp->sym->type);
		       				if (p->type->op == UNSIGNED)
		       					p->u.v.i = extend(p->u.v.u, p->type);
		       				needconst--;
		       				caselabel(swp, p->u.v.i, lab);
		       			}
		       		} else
		       			error("case label must be a constant integer expression\n");

		       		test(':', stop);
		       	}
		       	statement(loop, swp, lev);
		       } break;
	case DEFAULT:  if (swp == NULL)
		       	error("illegal default label\n");
		       else if (swp->deflab)
		       	error("extra default label\n");
		       else {
		       	swp->deflab = findlabel(swp->lab);
		       	definelab(swp->deflab->u.l.label);
		       }
		       t = gettok();
		       expect(':');
		       statement(loop, swp, lev); break;
	case RETURN:   {
		       	Type rty = freturn(cfunc->type);
		       	t = gettok();
		       	definept(NULL);
		       	if (t != ';')
		       		if (rty == voidtype) {
		       			error("extraneous return value\n");
		       			expr(0);
		       			retcode(NULL);
		       		} else
		       			retcode(expr(0));
		       	else {
		       		if (rty != voidtype)
		       			warning("missing return value\n");
		       		retcode(NULL);
		       	}
		       	branch(cfunc->u.f.label);
		       } expect(';');
					    break;

	case '{':      compound(loop, swp, lev + 1); break;
	case ';':      definept(NULL); t = gettok(); break;
	case GOTO:     walk(NULL, 0, 0);
		       definept(NULL);
		       t = gettok();
		       if (t == ID) {
		       	Symbol p = lookup(token, stmtlabs);
		       	if (p == NULL) {
				p = install(token, &stmtlabs, 0, FUNC);
				p->scope = LABELS;
				p->u.l.label = genlabel(1);
				p->src = src;
			}
		       	use(p, src);
		       	branch(p->u.l.label);
		       	t = gettok();
		       } else
		       	error("missing label in goto\n"); expect(';');
					  break;

	case ID:       if (getchr() == ':') {
		       	stmtlabel();
		       	statement(loop, swp, lev);
		       	break;
		       }
	default:       definept(NULL);
		       if (kind[t] != ID) {
		       	error("unrecognized statement\n");
		       	t = gettok();
		       } else {
		       	Tree e = expr0(0);
		       	listnodes(e, 0, 0);
		       	if (nodecount == 0 || nodecount > 200)
		       		walk(NULL, 0, 0);
		       	else if (glevel) walk(NULL, 0, 0);
		       	deallocate(STMT);
		       } expect(';');
						break;

	}
	if (kind[t] != IF && kind[t] != ID
	&& t != '}' && t != EOI) {
		static char stop[] = { IF, ID, '}', 0 };
		error("illegal statement termination\n");
		skipto(0, stop);
	}
	refinc = ref;
}