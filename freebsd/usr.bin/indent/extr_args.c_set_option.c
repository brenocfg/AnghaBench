#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pro {char* p_name; int p_type; int p_special; int* p_obj; } ;
struct TYPE_2__ {int /*<<< orphan*/  case_indent; } ;

/* Variables and functions */
#define  CLI 136 
#define  IGN 135 
 char* INDENT_VERSION ; 
#define  KEY 134 
#define  KEY_FILE 133 
 int OFF ; 
#define  PRO_BOOL 132 
#define  PRO_INT 131 
#define  PRO_SPECIAL 130 
#define  STDIN 129 
#define  VERSION 128 
 int /*<<< orphan*/  add_typedefs_from_file (char const*) ; 
 int /*<<< orphan*/  add_typename (char const*) ; 
 int /*<<< orphan*/  atof (char const*) ; 
 int atoi (char const*) ; 
 char* eqin (char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * input ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 TYPE_1__ opt ; 
 int /*<<< orphan*/  option_source ; 
 int /*<<< orphan*/ * output ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 struct pro* pro ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 

void
set_option(char *arg)
{
    struct	pro *p;
    const char	*param_start;

    arg++;			/* ignore leading "-" */
    for (p = pro; p->p_name; p++)
	if (*p->p_name == *arg && (param_start = eqin(p->p_name, arg)) != NULL)
	    goto found;
    errx(1, "%s: unknown parameter \"%s\"", option_source, arg - 1);
found:
    switch (p->p_type) {

    case PRO_SPECIAL:
	switch (p->p_special) {

	case IGN:
	    break;

	case CLI:
	    if (*param_start == 0)
		goto need_param;
	    opt.case_indent = atof(param_start);
	    break;

	case STDIN:
	    if (input == NULL)
		input = stdin;
	    if (output == NULL)
		output = stdout;
	    break;

	case KEY:
	    if (*param_start == 0)
		goto need_param;
	    add_typename(param_start);
	    break;

	case KEY_FILE:
	    if (*param_start == 0)
		goto need_param;
	    add_typedefs_from_file(param_start);
	    break;

	case VERSION:
	    printf("FreeBSD indent %s\n", INDENT_VERSION);
	    exit(0);

	default:
	    errx(1, "set_option: internal error: p_special %d", p->p_special);
	}
	break;

    case PRO_BOOL:
	if (p->p_special == OFF)
	    *p->p_obj = false;
	else
	    *p->p_obj = true;
	break;

    case PRO_INT:
	if (!isdigit((unsigned char)*param_start)) {
    need_param:
	    errx(1, "%s: ``%s'' requires a parameter", option_source, p->p_name);
	}
	*p->p_obj = atoi(param_start);
	break;

    default:
	errx(1, "set_option: internal error: p_type %d", p->p_type);
    }
}