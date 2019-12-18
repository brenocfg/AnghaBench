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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int INBUFSIZE ; 
#define  S_CODE 142 
#define  S_COMMENT 141 
#define  S_DISCARD 140 
#define  S_KEYWORD 139 
#define  T_COMMENT 138 
#define  T_ENDCODE 137 
#define  T_ENDDEF 136 
#define  T_HOSTTYPE 135 
#define  T_MACHTYPE 134 
#define  T_MACRO 133 
#define  T_NEWCODE 132 
#define  T_NEWDEF 131 
#define  T_NONE 130 
#define  T_OSTYPE 129 
#define  T_VENDOR 128 
 char* explode (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int findtoken (char*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* gettoken (char**,char*) ; 
 char** keyword ; 
 char* pname ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  stdout ; 
 char* strrchr (char*,char) ; 

int
main(int argc, char *argv[])
{
    char line[INBUFSIZE];
    const char *fname = "stdin";
    char *ptr, *tok;
    char defs[INBUFSIZE];
    char stmt[INBUFSIZE];
    FILE *fp = stdin;
    int lineno = 0;
    int inprocess = 0;
    int token, state;
    int errs = 0;

    if ((pname = strrchr(argv[0], '/')) == NULL)
	pname = argv[0];
    else
	pname++;

    if (argc > 2) {
	(void) fprintf(stderr, "Usage: %s [<filename>]\n", pname);
	return 1;
    }

    if (argc == 2)
	if ((fp = fopen(fname = argv[1], "r")) == NULL) {
	    (void) fprintf(stderr, "%s: Cannot open `%s'\n", pname, fname);
	    return 1;
	}

    state = S_DISCARD;

    while ((ptr = fgets(line, sizeof(line), fp)) != NULL) {
	lineno++;
	switch (token = findtoken(gettoken(&ptr, defs))) {
	case T_NEWCODE:
	    state = S_CODE;
	    break;

	case T_ENDCODE:
	    state = S_DISCARD;
	    break;

	case T_COMMENT:
	    state = S_COMMENT;
	    break;

	case T_NEWDEF:
	    state = S_KEYWORD;
	    break;

	case T_ENDDEF:
	    state = S_DISCARD;
	    break;

	case T_VENDOR:
	    state = S_KEYWORD;
	    break;

	case T_HOSTTYPE:
	    state = S_KEYWORD;
	    break;

	case T_MACHTYPE:
	    state = S_KEYWORD;
	    break;

	case T_OSTYPE:
	    state = S_KEYWORD;
	    break;

	case T_MACRO:
	    if (gettoken(&ptr, defs) == NULL) {
		(void) fprintf(stderr, "%s: \"%s\", %d: Missing macro name\n",
			       pname, fname, lineno);
		break;
	    }
	    if (gettoken(&ptr, stmt) == NULL) {
		(void) fprintf(stderr, "%s: \"%s\", %d: Missing macro body\n",
			       pname, fname, lineno);
		break;
	    }
	    (void) fprintf(stdout, "\n#if %s\n# define %s\n#endif\n\n",
		explode(stmt), defs);
	    break;

	case T_NONE:
	    if (state != S_CODE && *defs != '\0') {
		(void) fprintf(stderr, "%s: \"%s\", %d: Discarded\n",
			       pname, fname, lineno);
		if (++errs == 30) {
		    (void) fprintf(stderr, "%s: Too many errors\n", pname);
		    return 1;
		}
		break;
	    }
	    (void) fprintf(stdout, "%s", line);
	    break;

	default:
	    (void) fprintf(stderr, "%s: \"%s\", %d: Unexpected token\n",
			   pname, fname, lineno);
	    return 1;
	}

	switch (state) {
	case S_DISCARD:
	    if (inprocess) {
		inprocess = 0;
		(void) fprintf(stdout, "#endif\n");
	    }
	    break;

	case S_KEYWORD:
	    tok = gettoken(&ptr, defs);
	    if (token == T_NEWDEF) {
		if (inprocess) {
		    (void) fprintf(stderr, "%s: \"%s\", %d: Missing enddef\n",
				   pname, fname, lineno);
		    return 1;
		}
		if (tok == NULL) {
		    (void) fprintf(stderr, "%s: \"%s\", %d: No defs\n",
				   pname, fname, lineno);
		    return 1;
		}
		(void) fprintf(stdout, "\n\n");
#ifdef LINEDIRECTIVE
		(void) fprintf(stdout, "# %d \"%s\"\n", lineno + 1, fname);
#endif /* LINEDIRECTIVE */
		(void) fprintf(stdout, "#if (%s)\n", explode(defs));
		inprocess = 1;
	    }
	    else {
		if (tok && *tok)
		    (void) fprintf(stdout, "# if (%s) && !defined(_%s_)\n",
				   explode(defs), keyword[token]);
		else
		    (void) fprintf(stdout, "# if !defined(_%s_)\n", 
				   keyword[token]);

		if (gettoken(&ptr, stmt) == NULL) {
		    (void) fprintf(stderr, "%s: \"%s\", %d: No statement\n",
				   pname, fname, lineno);
		    return 1;
		}
		(void) fprintf(stdout, "# define _%s_\n", keyword[token]);
		(void) fprintf(stdout, "    %s = %s;\n", keyword[token], stmt);
		(void) fprintf(stdout, "# endif\n");
	    }
	    break;

	case S_COMMENT:
	    if (gettoken(&ptr, defs))
		(void) fprintf(stdout, "    /* %s */\n", defs);
	    break;

	case S_CODE:
	    if (token == T_NEWCODE) {
#ifdef LINEDIRECTIVE
		(void) fprintf(stdout, "# %d \"%s\"\n", lineno + 1, fname);
#endif /* LINEDIRECTIVE */
	    }
	    break;

	default:
	    (void) fprintf(stderr, "%s: \"%s\", %d: Unexpected state\n",
			   pname, fname, lineno);
	    return 1;
	}
    }

    if (inprocess) {
	(void) fprintf(stderr, "%s: \"%s\", %d: Missing enddef\n",
		       pname, fname, lineno);
	return 1;
    }

    if (fp != stdin)
	(void) fclose(fp);

    return 0;
}