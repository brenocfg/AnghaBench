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
 int /*<<< orphan*/  CGETS (size_t,int,char*) ; 
 scalar_t__ CSAVS (int,int,char*) ; 
 size_t ERR_ALIASLOOP ; 
 size_t ERR_AMBIG ; 
 size_t ERR_ARCH ; 
 size_t ERR_ARGC ; 
 size_t ERR_ASSIGN ; 
 size_t ERR_BADBANG ; 
 size_t ERR_BADBANGARG ; 
 size_t ERR_BADBANGMOD ; 
 size_t ERR_BADCOLORVAR ; 
 size_t ERR_BADDIR ; 
 size_t ERR_BADJOB ; 
 size_t ERR_BADMOD ; 
 size_t ERR_BADNUM ; 
 size_t ERR_BADPLP ; 
 size_t ERR_BADPLPS ; 
 size_t ERR_BADSCALE ; 
 size_t ERR_BADSIG ; 
 size_t ERR_BADSUBST ; 
 size_t ERR_CANTCHANGE ; 
 size_t ERR_COMMAND ; 
 size_t ERR_COMPCOM ; 
 size_t ERR_COMPINC ; 
 size_t ERR_COMPINV ; 
 size_t ERR_COMPMIS ; 
 size_t ERR_DANGER ; 
 size_t ERR_DEEP ; 
 size_t ERR_DIGIT ; 
 size_t ERR_DIRUS ; 
 size_t ERR_DIV0 ; 
 size_t ERR_DOLZERO ; 
 size_t ERR_EMPTY ; 
 size_t ERR_EMPTYIF ; 
 size_t ERR_EOF ; 
 size_t ERR_EXISTS ; 
 size_t ERR_EXPORD ; 
 size_t ERR_EXPOVFL ; 
 size_t ERR_EXPRESSION ; 
 size_t ERR_FILEINQ ; 
 size_t ERR_FILENAME ; 
 size_t ERR_GLOB ; 
 size_t ERR_HFLAG ; 
 size_t ERR_HISTLOOP ; 
 size_t ERR_HISTUS ; 
 size_t ERR_IMPRTHEN ; 
 size_t ERR_INCBR ; 
 size_t ERR_INRED ; 
 size_t ERR_INTR ; 
 size_t ERR_JOBARGS ; 
 size_t ERR_JOBCONTROL ; 
 size_t ERR_JOBCTRLSUB ; 
 size_t ERR_JOBCUR ; 
 size_t ERR_JOBPAT ; 
 size_t ERR_JOBPREV ; 
 size_t ERR_JOBS ; 
 size_t ERR_LHS ; 
 size_t ERR_LIMIT ; 
 size_t ERR_LTOOLONG ; 
 size_t ERR_MASK ; 
 size_t ERR_MFLAG ; 
 size_t ERR_MISRED ; 
 size_t ERR_MISSING ; 
 size_t ERR_MOD0 ; 
 size_t ERR_MODFAIL ; 
 size_t ERR_NESTING ; 
 size_t ERR_NEWLINE ; 
 size_t ERR_NLINDEX ; 
 size_t ERR_NODIR ; 
 size_t ERR_NOEVENT ; 
 size_t ERR_NOHOME ; 
 size_t ERR_NOHOMEDIR ; 
 size_t ERR_NOMATCH ; 
 size_t ERR_NOMEM ; 
 size_t ERR_NOMORE ; 
 size_t ERR_NOPAREN ; 
 size_t ERR_NOPROC ; 
 size_t ERR_NOSCHED ; 
 size_t ERR_NOSEARCH ; 
 size_t ERR_NOSUBST ; 
 size_t ERR_NOSUCHJOB ; 
 size_t ERR_NOTALLOWED ; 
 size_t ERR_NOTFOUND ; 
 size_t ERR_NOTLOGIN ; 
 size_t ERR_NOTWHILE ; 
 size_t ERR_NOWATCH ; 
 size_t ERR_NULLCOM ; 
 size_t ERR_OUTRED ; 
 size_t ERR_OVERFLOW ; 
 size_t ERR_PIPE ; 
 size_t ERR_RANGE ; 
 size_t ERR_READONLY ; 
 size_t ERR_REDPAR ; 
 size_t ERR_RHSLONG ; 
 size_t ERR_SCALEF ; 
 size_t ERR_SCHEDCOM ; 
 size_t ERR_SCHEDEV ; 
 size_t ERR_SCHEDREL ; 
 size_t ERR_SCHEDTIME ; 
 size_t ERR_SCHEDUSAGE ; 
 size_t ERR_SELOVFL ; 
 size_t ERR_SETTCUS ; 
 size_t ERR_SPDOLLT ; 
 size_t ERR_SPSTAR ; 
 size_t ERR_STOPPED ; 
 size_t ERR_STRING ; 
 size_t ERR_SUBOVFL ; 
 size_t ERR_SUBSCRIPT ; 
 size_t ERR_SUSPLOG ; 
 size_t ERR_SYNC ; 
 size_t ERR_SYNTAX ; 
 size_t ERR_SYSTEM ; 
 size_t ERR_TCARGS ; 
 size_t ERR_TCCAP ; 
 size_t ERR_TCNARGS ; 
 size_t ERR_TCNOSTR ; 
 size_t ERR_TCPARM ; 
 size_t ERR_TCSHUSAGE ; 
 size_t ERR_TCUSAGE ; 
 size_t ERR_TERMINAL ; 
 size_t ERR_TOOFEW ; 
 size_t ERR_TOOLARGE ; 
 size_t ERR_TOOMANY ; 
 size_t ERR_TOOMANYLP ; 
 size_t ERR_TOOMANYRP ; 
 size_t ERR_ULIMUS ; 
 size_t ERR_UNDVAR ; 
 size_t ERR_UNKNOWNOP ; 
 size_t ERR_UNKSIG ; 
 size_t ERR_UNKUSER ; 
 size_t ERR_UNMATCHED ; 
 size_t ERR_VARALNUM ; 
 size_t ERR_VARBEGIN ; 
 size_t ERR_VARILL ; 
 size_t ERR_VARSYN ; 
 size_t ERR_VARTOOLONG ; 
 size_t ERR_WTOOLONG ; 
 size_t NLS_MAXSET ; 
 size_t NO_ERRORS ; 
 scalar_t__* elst ; 
 int /*<<< orphan*/  xfree (char*) ; 

void
errinit(void)
{
#ifdef NLS_CATALOGS
    size_t i;

    for (i = 0; i < NO_ERRORS; i++)
	xfree((char *)(intptr_t)elst[i]);
#  if defined(__FreeBSD__) || defined(hpux) || defined(__MidnightBSD__)
#  define NLS_MAXSET 30
    for (i = 1; i <= NLS_MAXSET; i++)
	CGETS(i, 1, "" );
#  endif
#endif

    elst[ERR_SYNTAX] = CSAVS(1, 1, "Syntax Error");
    elst[ERR_NOTALLOWED] = CSAVS(1, 2, "%s is not allowed");
    elst[ERR_WTOOLONG] = CSAVS(1, 3, "Word too long");
    elst[ERR_LTOOLONG] = CSAVS(1, 4, "$< line too long");
    elst[ERR_DOLZERO] = CSAVS(1, 5, "No file for $0");
    elst[ERR_INCBR] = CSAVS(1, 6, "Incomplete [] modifier");
    elst[ERR_EXPORD] = CSAVS(1, 7, "$ expansion must end before ]");
    elst[ERR_BADMOD] = CSAVS(1, 8, "Bad : modifier in $ '%c'");
    elst[ERR_SUBSCRIPT] = CSAVS(1, 9, "Subscript error");
    elst[ERR_BADNUM] = CSAVS(1, 10, "Badly formed number");
    elst[ERR_NOMORE] = CSAVS(1, 11, "No more words");
    elst[ERR_FILENAME] = CSAVS(1, 12, "Missing file name");
    elst[ERR_GLOB] = CSAVS(1, 13, "Internal glob error");
    elst[ERR_COMMAND] = CSAVS(1, 14, "Command not found");
    elst[ERR_TOOFEW] = CSAVS(1, 15, "Too few arguments");
    elst[ERR_TOOMANY] = CSAVS(1, 16, "Too many arguments");
    elst[ERR_DANGER] = CSAVS(1, 17, "Too dangerous to alias that");
    elst[ERR_EMPTYIF] = CSAVS(1, 18, "Empty if");
    elst[ERR_IMPRTHEN] = CSAVS(1, 19, "Improper then");
    elst[ERR_NOPAREN] = CSAVS(1, 20, "Words not parenthesized");
    elst[ERR_NOTFOUND] = CSAVS(1, 21, "%s not found");
    elst[ERR_MASK] = CSAVS(1, 22, "Improper mask");
    elst[ERR_LIMIT] = CSAVS(1, 23, "No such limit");
    elst[ERR_TOOLARGE] = CSAVS(1, 24, "Argument too large");
    elst[ERR_SCALEF] = CSAVS(1, 25, "Improper or unknown scale factor");
    elst[ERR_UNDVAR] = CSAVS(1, 26, "Undefined variable");
    elst[ERR_DEEP] = CSAVS(1, 27, "Directory stack not that deep");
    elst[ERR_BADSIG] = CSAVS(1, 28, "Bad signal number");
    elst[ERR_UNKSIG] = CSAVS(1, 29, "Unknown signal; kill -l lists signals");
    elst[ERR_VARBEGIN] = CSAVS(1, 30, "Variable name must begin with a letter");
    elst[ERR_VARTOOLONG] = CSAVS(1, 31, "Variable name too long");
    elst[ERR_VARALNUM] = CSAVS(1, 32,
	"Variable name must contain alphanumeric characters");
    elst[ERR_JOBCONTROL] = CSAVS(1, 33, "No job control in this shell");
    elst[ERR_EXPRESSION] = CSAVS(1, 34, "Expression Syntax");
    elst[ERR_NOHOMEDIR] = CSAVS(1, 35, "No home directory");
    elst[ERR_CANTCHANGE] = CSAVS(1, 36, "Can't change to home directory");
    elst[ERR_NULLCOM] = CSAVS(1, 37, "Invalid null command");
    elst[ERR_ASSIGN] = CSAVS(1, 38, "Assignment missing expression");
    elst[ERR_UNKNOWNOP] = CSAVS(1, 39, "Unknown operator");
    elst[ERR_AMBIG] = CSAVS(1, 40, "Ambiguous");
    elst[ERR_EXISTS] = CSAVS(1, 41, "%s: File exists");
    elst[ERR_ARGC] = CSAVS(1, 42, "Argument for -c ends in backslash");
    elst[ERR_INTR] = CSAVS(1, 43, "Interrupted");
    elst[ERR_RANGE] = CSAVS(1, 44, "Subscript out of range");
    elst[ERR_OVERFLOW] = CSAVS(1, 45, "Line overflow");
    elst[ERR_NOSUCHJOB] = CSAVS(1, 46, "No such job");
    elst[ERR_TERMINAL] = CSAVS(1, 47, "Can't from terminal");
    elst[ERR_NOTWHILE] = CSAVS(1, 48, "Not in while/foreach");
    elst[ERR_NOPROC] = CSAVS(1, 49, "No more processes");
    elst[ERR_NOMATCH] = CSAVS(1, 50, "No match");
    elst[ERR_MISSING] = CSAVS(1, 51, "Missing '%c'");
    elst[ERR_UNMATCHED] = CSAVS(1, 52, "Unmatched '%c'");
    elst[ERR_NOMEM] = CSAVS(1, 53, "Out of memory");
    elst[ERR_PIPE] = CSAVS(1, 54, "Can't make pipe");
    elst[ERR_SYSTEM] = CSAVS(1, 55, "%s: %s");
    elst[ERR_STRING] = CSAVS(1, 56, "%s");
    elst[ERR_JOBS] = CSAVS(1, 57, "Usage: jobs [ -l ]");
    elst[ERR_JOBARGS] = CSAVS(1, 58, "Arguments should be jobs or process id's");
    elst[ERR_JOBCUR] = CSAVS(1, 59, "No current job");
    elst[ERR_JOBPREV] = CSAVS(1, 60, "No previous job");
    elst[ERR_JOBPAT] = CSAVS(1, 61, "No job matches pattern");
    elst[ERR_NESTING] = CSAVS(1, 62, "Fork nesting > %d; maybe `...` loop");
    elst[ERR_JOBCTRLSUB] = CSAVS(1, 63, "No job control in subshells");
    elst[ERR_SYNC] = CSAVS(1, 64, "Sync fault: Process %d not found");
    elst[ERR_STOPPED] =
#ifdef SUSPENDED
	CSAVS(1, 65, "%sThere are suspended jobs");
#else
	CSAVS(1, 66, "%sThere are stopped jobs");
#endif /* SUSPENDED */
    elst[ERR_NODIR] = CSAVS(1, 67, "No other directory");
    elst[ERR_EMPTY] = CSAVS(1, 68, "Directory stack empty");
    elst[ERR_BADDIR] = CSAVS(1, 69, "Bad directory");
    elst[ERR_DIRUS] = CSAVS(1, 70, "Usage: %s [-%s]%s");
    elst[ERR_HFLAG] = CSAVS(1, 71, "No operand for -h flag");
    elst[ERR_NOTLOGIN] = CSAVS(1, 72, "Not a login shell");
    elst[ERR_DIV0] = CSAVS(1, 73, "Division by 0");
    elst[ERR_MOD0] = CSAVS(1, 74, "Mod by 0");
    elst[ERR_BADSCALE] = CSAVS(1, 75, "Bad scaling; did you mean \"%s\"?");
    elst[ERR_SUSPLOG] = CSAVS(1, 76, "Can't suspend a login shell (yet)");
    elst[ERR_UNKUSER] = CSAVS(1, 77, "Unknown user: %s");
    elst[ERR_NOHOME] = CSAVS(1, 78, "No $home variable set");
    elst[ERR_HISTUS] = CSAVS(1, 79,
	"Usage: history [-%s] [# number of events]");
    elst[ERR_SPDOLLT] = CSAVS(1, 80, "$, ! or < not allowed with $# or $?");
    elst[ERR_NEWLINE] = CSAVS(1, 81, "Newline in variable name");
    elst[ERR_SPSTAR] = CSAVS(1, 82, "* not allowed with $# or $?");
    elst[ERR_DIGIT] = CSAVS(1, 83, "$?<digit> or $#<digit> not allowed");
    elst[ERR_VARILL] = CSAVS(1, 84, "Illegal variable name");
    elst[ERR_NLINDEX] = CSAVS(1, 85, "Newline in variable index");
    elst[ERR_EXPOVFL] = CSAVS(1, 86, "Expansion buffer overflow");
    elst[ERR_VARSYN] = CSAVS(1, 87, "Variable syntax");
    elst[ERR_BADBANG] = CSAVS(1, 88, "Bad ! form");
    elst[ERR_NOSUBST] = CSAVS(1, 89, "No previous substitute");
    elst[ERR_BADSUBST] = CSAVS(1, 90, "Bad substitute");
    elst[ERR_LHS] = CSAVS(1, 91, "No previous left hand side");
    elst[ERR_RHSLONG] = CSAVS(1, 92, "Right hand side too long");
    elst[ERR_BADBANGMOD] = CSAVS(1, 93, "Bad ! modifier: '%c'");
    elst[ERR_MODFAIL] = CSAVS(1, 94, "Modifier failed");
    elst[ERR_SUBOVFL] = CSAVS(1, 95, "Substitution buffer overflow");
    elst[ERR_BADBANGARG] = CSAVS(1, 96, "Bad ! arg selector");
    elst[ERR_NOSEARCH] = CSAVS(1, 97, "No prev search");
    elst[ERR_NOEVENT] = CSAVS(1, 98, "%s: Event not found");
    elst[ERR_TOOMANYRP] = CSAVS(1, 99, "Too many )'s");
    elst[ERR_TOOMANYLP] = CSAVS(1, 100, "Too many ('s");
    elst[ERR_BADPLP] = CSAVS(1, 101, "Badly placed (");
    elst[ERR_MISRED] = CSAVS(1, 102, "Missing name for redirect");
    elst[ERR_OUTRED] = CSAVS(1, 103, "Ambiguous output redirect");
    elst[ERR_REDPAR] = CSAVS(1, 104, "Can't << within ()'s");
    elst[ERR_INRED] = CSAVS(1, 105, "Ambiguous input redirect");
    elst[ERR_BADPLPS] = CSAVS(1, 106, "Badly placed ()'s");
    elst[ERR_ALIASLOOP] = CSAVS(1, 107, "Alias loop");
    elst[ERR_NOWATCH] = CSAVS(1, 108, "No $watch variable set");
    elst[ERR_NOSCHED] = CSAVS(1, 109, "No scheduled events");
    elst[ERR_SCHEDUSAGE] = CSAVS(1, 110,
	"Usage: sched -<item#>.\nUsage: sched [+]hh:mm <command>");
    elst[ERR_SCHEDEV] = CSAVS(1, 111, "Not that many scheduled events");
    elst[ERR_SCHEDCOM] = CSAVS(1, 112, "No command to run");
    elst[ERR_SCHEDTIME] = CSAVS(1, 113, "Invalid time for event");
    elst[ERR_SCHEDREL] = CSAVS(1, 114, "Relative time inconsistent with am/pm");
    elst[ERR_TCNOSTR] = CSAVS(1, 115, "Out of termcap string space");
    elst[ERR_SETTCUS] = CSAVS(1, 116, "Usage: settc %s [yes|no]");
    elst[ERR_TCCAP] = CSAVS(1, 117, "Unknown capability `%s'");
    elst[ERR_TCPARM] = CSAVS(1, 118, "Unknown termcap parameter '%%%c'");
    elst[ERR_TCARGS] = CSAVS(1, 119, "Too many arguments for `%s' (%d)");
    elst[ERR_TCNARGS] = CSAVS(1, 120, "`%s' requires %d arguments");
    elst[ERR_TCUSAGE] = CSAVS(1, 121,
	"Usage: echotc [-v|-s] [<capability> [<args>]]");
    elst[ERR_ARCH] = CSAVS(1, 122, "%s: %s. Binary file not executable");
    elst[ERR_HISTLOOP] = CSAVS(1, 123, "!# History loop");
    elst[ERR_FILEINQ] = CSAVS(1, 124, "Malformed file inquiry");
    elst[ERR_SELOVFL] = CSAVS(1, 125, "Selector overflow");
#ifdef apollo
    elst[ERR_TCSHUSAGE] = CSAVS(1, 126,
"Unknown option: `-%s'\nUsage: %s [ -bcdefilmnqstvVxX -Dname[=value] ] [ argument ... ]");
#else /* !apollo */
# ifdef convex
    elst[ERR_TCSHUSAGE] = CSAVS(1, 127,
"Unknown option: `-%s'\nUsage: %s [ -bcdefFilmnqstvVxX ] [ argument ... ]");
# else /* rest */
    elst[ERR_TCSHUSAGE] = CSAVS(1, 128,
"Unknown option: `-%s'\nUsage: %s [ -bcdefilmnqstvVxX ] [ argument ... ]");
# endif /* convex */
#endif /* apollo */
    elst[ERR_COMPCOM] = CSAVS(1, 129, "\nInvalid completion: \"%s\"");
    elst[ERR_COMPINV] = CSAVS(1, 130, "\nInvalid %s: '%c'");
    elst[ERR_COMPMIS] = CSAVS(1, 131,
	"\nMissing separator '%c' after %s \"%s\"");
    elst[ERR_COMPINC] = CSAVS(1, 132, "\nIncomplete %s: \"%s\"");
    elst[ERR_MFLAG] = CSAVS(1, 133, "No operand for -m flag");
    elst[ERR_ULIMUS] = CSAVS(1, 134, "Usage: unlimit [-fh] [limits]");
    elst[ERR_READONLY] = CSAVS(1, 135, "$%S is read-only");
    elst[ERR_BADJOB] = CSAVS(1, 136, "No such job (badjob)");
    elst[ERR_BADCOLORVAR] = CSAVS(1, 137, "Unknown colorls variable '%c%c'");
    elst[ERR_EOF] = CSAVS(1, 138, "Unexpected end of file");
}