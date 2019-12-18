#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uChar ;
struct command {int dummy; } ;
struct TYPE_12__ {int* buf; int len; } ;
typedef  scalar_t__ KEYCMD ;
typedef  char Char ;
typedef  TYPE_1__ CStr ;

/* Variables and functions */
 int /*<<< orphan*/  AddXkey (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BindArrowKeys () ; 
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 char CHAR ; 
 scalar_t__* CcAltMap ; 
 scalar_t__* CcKeyMap ; 
 int /*<<< orphan*/  ClearArrowKeys (TYPE_1__*) ; 
 int /*<<< orphan*/  ClearXkey (scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteXkey (TYPE_1__*) ; 
 scalar_t__ F_UNASSIGNED ; 
 scalar_t__ F_XKEY ; 
 int /*<<< orphan*/  IsArrowKey (char*) ; 
 int /*<<< orphan*/  MapsAreInited ; 
 int /*<<< orphan*/  PrintArrowKeys (TYPE_1__*) ; 
 int SetArrowKeys (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int Strlen (int*) ; 
 int* Strsave (char*) ; 
 int /*<<< orphan*/  USE (struct command*) ; 
#define  XK_CMD 130 
#define  XK_EXE 129 
#define  XK_STR 128 
 int /*<<< orphan*/  XmapCmd (int) ; 
 int /*<<< orphan*/  XmapStr (TYPE_1__*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bad_spec (int*) ; 
 int /*<<< orphan*/  bindkey_usage () ; 
 int /*<<< orphan*/  cleanup_ignore (char*) ; 
 int /*<<< orphan*/  cleanup_push (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int*) ; 
 int /*<<< orphan*/  ed_InitEmacsMaps () ; 
 int /*<<< orphan*/  ed_InitMaps () ; 
 int /*<<< orphan*/  ed_InitVIMaps () ; 
 int /*<<< orphan*/  list_functions () ; 
 int /*<<< orphan*/ * parsebind (char*,TYPE_1__*) ; 
 scalar_t__ parsecmd (char*) ; 
 int /*<<< orphan*/ * parsestring (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  print_all_keys () ; 
 int /*<<< orphan*/  printkey (scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  xfree ; 
 int /*<<< orphan*/  xprintf (int /*<<< orphan*/ ,char*) ; 

void
dobindkey(Char **v, struct command *c)
{
    KEYCMD *map;
    int     ntype, no, removeb, key, bindk;
    Char   *par;
    Char    p;
    KEYCMD  cmd;
    CStr    in;
    CStr    out;
    uChar   ch;

    USE(c);
    if (!MapsAreInited)
	ed_InitMaps();

    map = CcKeyMap;
    ntype = XK_CMD;
    key = removeb = bindk = 0;
    for (no = 1, par = v[no]; 
	 par != NULL && (*par++ & CHAR) == '-'; no++, par = v[no]) {
	if ((p = (*par & CHAR)) == '-') {
	    no++;
	    break;
	}
	else 
	    switch (p) {
	    case 'b':
		bindk = 1;
		break;
	    case 'k':
		key = 1;
		break;
	    case 'a':
		map = CcAltMap;
		break;
	    case 's':
		ntype = XK_STR;
		break;
	    case 'c':
		ntype = XK_EXE;
		break;
	    case 'r':
		removeb = 1;
		break;
	    case 'v':
		ed_InitVIMaps();
		return;
	    case 'e':
		ed_InitEmacsMaps();
		return;
	    case 'd':
#ifdef VIDEFAULT
		ed_InitVIMaps();
#else /* EMACSDEFAULT */
		ed_InitEmacsMaps();
#endif /* VIDEFAULT */
		return;
	    case 'l':
		list_functions();
		return;
	    default:
		bindkey_usage();
		return;
	    }
    }

    if (!v[no]) {
	print_all_keys();
	return;
    }

    if (key) {
	if (!IsArrowKey(v[no]))
	    xprintf(CGETS(20, 1, "Invalid key name `%S'\n"), v[no]);
	in.buf = Strsave(v[no++]);
	in.len = Strlen(in.buf);
    }
    else {
	if (bindk) {
	    if (parsebind(v[no++], &in) == NULL)
		return;
	}
	else {
	    if (parsestring(v[no++], &in) == NULL)
		return;
	}
    }
    cleanup_push(in.buf, xfree);

#ifndef WINNT_NATIVE
    if (in.buf[0] > 0xFF) {
	bad_spec(in.buf);
	cleanup_until(in.buf);
	return;
    }
#endif
    ch = (uChar) in.buf[0];

    if (removeb) {
	if (key)
	    (void) ClearArrowKeys(&in);
	else if (in.len > 1) {
	    (void) DeleteXkey(&in);
	}
	else if (map[ch] == F_XKEY) {
	    (void) DeleteXkey(&in);
	    map[ch] = F_UNASSIGNED;
	}
	else {
	    map[ch] = F_UNASSIGNED;
	}
	cleanup_until(in.buf);
	return;
    }
    if (!v[no]) {
	if (key)
	    PrintArrowKeys(&in);
	else
	    printkey(map, &in);
	cleanup_until(in.buf);
	return;
    }
    if (v[no + 1]) {
	bindkey_usage();
	cleanup_until(in.buf);
	return;
    }
    switch (ntype) {
    case XK_STR:
    case XK_EXE:
	if (parsestring(v[no], &out) == NULL) {
	    cleanup_until(in.buf);
	    return;
	}
	cleanup_push(out.buf, xfree);
	if (key) {
	    if (SetArrowKeys(&in, XmapStr(&out), ntype) == -1)
		xprintf(CGETS(20, 2, "Bad key name: %S\n"), in.buf);
	    else
		cleanup_ignore(out.buf);
	}
	else
	    AddXkey(&in, XmapStr(&out), ntype);
	map[ch] = F_XKEY;
	break;
    case XK_CMD:
	if ((cmd = parsecmd(v[no])) == 0) {
	    cleanup_until(in.buf);
	    return;
	}
	if (key)
	    (void) SetArrowKeys(&in, XmapCmd((int) cmd), ntype);
	else {
	    if (in.len > 1) {
		AddXkey(&in, XmapCmd((int) cmd), ntype);
		map[ch] = F_XKEY;
	    }
	    else {
		ClearXkey(map, &in);
		map[ch] = cmd;
	    }
	}
	break;
    default:
	abort();
	break;
    }
    cleanup_until(in.buf);
    if (key)
	BindArrowKeys();
}