#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct symbol {int defined; TYPE_3__* type; } ;
typedef  TYPE_3__* Type ;
struct TYPE_11__ {int oldstyle; TYPE_3__** proto; } ;
struct TYPE_12__ {TYPE_1__ f; } ;
struct TYPE_13__ {TYPE_2__ u; } ;
typedef  struct symbol* Symbol ;
typedef  int /*<<< orphan*/ * List ;

/* Variables and functions */
 int Aflag ; 
#define  CHAR 130 
 size_t ELLIPSIS ; 
 int /*<<< orphan*/  FUNC ; 
 size_t ID ; 
#define  IF 129 
 int /*<<< orphan*/  PERM ; 
 size_t REGISTER ; 
#define  STATIC 128 
 int /*<<< orphan*/ * append (struct symbol*,int /*<<< orphan*/ *) ; 
 struct symbol* dclparam (int,char*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* dclr (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  expect (char) ; 
 size_t gettok () ; 
 int /*<<< orphan*/  hasproto (TYPE_3__*) ; 
 TYPE_3__* inttype ; 
 scalar_t__ istypename (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__* kind ; 
 scalar_t__ length (int /*<<< orphan*/ *) ; 
 struct symbol** ltov (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 TYPE_3__** newarray (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skipto (char,char*) ; 
 int /*<<< orphan*/  specifier (int*) ; 
 int /*<<< orphan*/  src ; 
 char* stringd (int) ; 
 size_t t ; 
 char* token ; 
 int /*<<< orphan*/  tsym ; 
 TYPE_3__* voidtype ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static Symbol *parameters(Type fty) {
	List list = NULL;
	Symbol *params;

	if (kind[t] == STATIC || istypename(t, tsym)) {
		int n = 0;
		Type ty1 = NULL;
		for (;;) {
			Type ty;
			int sclass = 0;
			char *id = NULL;
			if (ty1 && t == ELLIPSIS) {
				static struct symbol sentinel;
				if (sentinel.type == NULL) {
					sentinel.type = voidtype;
					sentinel.defined = 1;
				}
				if (ty1 == voidtype)
					error("illegal formal parameter types\n");
				list = append(&sentinel, list);
				t = gettok();
				break;
			}
			if (!istypename(t, tsym) && t != REGISTER)
				error("missing parameter type\n");
			n++;
			ty = dclr(specifier(&sclass), &id, NULL, 1);
			if ( (ty == voidtype && (ty1 || id))
			||  ty1 == voidtype)
				error("illegal formal parameter types\n");
			if (id == NULL)
				id = stringd(n);
			if (ty != voidtype)
				list = append(dclparam(sclass, id, ty, &src), list);
			if (Aflag >= 1 && !hasproto(ty))
				warning("missing prototype\n");
			if (ty1 == NULL)
				ty1 = ty;
			if (t != ',')
				break;
			t = gettok();
		}
		fty->u.f.proto = newarray(length(list) + 1,
			sizeof (Type *), PERM);
		params = ltov(&list, FUNC);
		for (n = 0; params[n]; n++)
			fty->u.f.proto[n] = params[n]->type;
		fty->u.f.proto[n] = NULL;
		fty->u.f.oldstyle = 0;
	} else {
		if (t == ID)
			for (;;) {
				Symbol p;
				if (t != ID) {
					error("expecting an identifier\n");
					break;
				}
				p = dclparam(0, token, inttype, &src);
				p->defined = 0;
				list = append(p, list);
				t = gettok();
				if (t != ',')
					break;
				t = gettok();
			}
		params = ltov(&list, FUNC);
		fty->u.f.proto = NULL;
		fty->u.f.oldstyle = 1;
	}
	if (t != ')') {
		static char stop[] = { CHAR, STATIC, IF, ')', 0 };
		expect(')');
		skipto('{', stop);
	}
	if (t == ')')
		t = gettok();
	return params;
}