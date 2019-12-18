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
struct varent {char** vec; } ;
struct Strbuf {int /*<<< orphan*/  s; } ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/ * Strchr (char*,char) ; 
 char* Strrchr (int /*<<< orphan*/ ,char) ; 
#define  TW_ALIAS 145 
#define  TW_BINDING 144 
#define  TW_COMMAND 143 
#define  TW_COMPLETION 142 
#define  TW_DIRECTORY 141 
#define  TW_ENVVAR 140 
#define  TW_FILE 139 
#define  TW_GRPNAME 138 
#define  TW_JOB 137 
#define  TW_LIMIT 136 
#define  TW_LOGNAME 135 
#define  TW_SHELLVAR 134 
#define  TW_SIGNAL 133 
#define  TW_TEXT 132 
#define  TW_USER 131 
#define  TW_VARIABLE 130 
#define  TW_VARLIST 129 
#define  TW_WORDLIST 128 
 struct varent* adrof (char*) ; 
 int /*<<< orphan*/  isadirectory (char const*,char*) ; 
 int /*<<< orphan*/  strip (char*) ; 
 char* tgetenv (char*) ; 

__attribute__((used)) static Char
tw_suffix(int looking, struct Strbuf *word, const Char *exp_dir, Char *exp_name)
{
    Char *ptr;
    Char *dol;
    struct varent *vp;

    (void) strip(exp_name);

    switch (looking) {

    case TW_LOGNAME:
	return '/';

    case TW_VARIABLE:
	/*
	 * Don't consider array variables or empty variables
	 */
	if ((vp = adrof(exp_name)) != NULL && vp->vec != NULL) {
	    if ((ptr = vp->vec[0]) == NULL || *ptr == '\0' ||
		vp->vec[1] != NULL) 
		return ' ';
	}
	else if ((ptr = tgetenv(exp_name)) == NULL || *ptr == '\0')
	    return ' ';

	if ((dol = Strrchr(word->s, '$')) != 0 && 
	    dol[1] == '{' && Strchr(dol, '}') == NULL)
	  return '}';

	return isadirectory(exp_dir, ptr) ? '/' : ' ';


    case TW_DIRECTORY:
	return '/';

    case TW_COMMAND:
    case TW_FILE:
	return isadirectory(exp_dir, exp_name) ? '/' : ' ';

    case TW_ALIAS:
    case TW_VARLIST:
    case TW_WORDLIST:
    case TW_SHELLVAR:
    case TW_ENVVAR:
    case TW_USER:
    case TW_BINDING:
    case TW_LIMIT:
    case TW_SIGNAL:
    case TW_JOB:
    case TW_COMPLETION:
    case TW_TEXT:
    case TW_GRPNAME:
	return ' ';

    default:
	return '\0';
    }
}