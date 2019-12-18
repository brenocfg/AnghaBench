#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ optEquivIndex; char* pz_Name; char* pz_DisableName; int /*<<< orphan*/  fOptState; } ;
typedef  TYPE_1__ tOptDesc ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLED_OPT (TYPE_1__*) ; 
 char NL ; 
 scalar_t__ NO_EQUIVALENT ; 
 scalar_t__ OPARG_TYPE_NUMERIC ; 
 scalar_t__ OPTST_GET_ARGTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char const*,size_t,size_t,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
prt_entry(FILE * fp, tOptDesc * od, char const * l_arg)
{
    int space_ct;

    /*
     *  There is an argument.  Pad the name so values line up.
     *  Not disabled *OR* this got equivalenced to another opt,
     *  then use current option name.
     *  Otherwise, there must be a disablement name.
     */
    {
        char const * pz =
            (! DISABLED_OPT(od) || (od->optEquivIndex != NO_EQUIVALENT))
            ? od->pz_Name
            : od->pz_DisableName;
        space_ct = 17 - strlen(pz);
        fputs(pz, fp);
    }

    if (  (l_arg == NULL)
       && (OPTST_GET_ARGTYPE(od->fOptState) != OPARG_TYPE_NUMERIC))
        goto end_entry;

    fputs(" = ", fp);
    while (space_ct-- > 0)  fputc(' ', fp);

    /*
     *  IF the option is numeric only,
     *  THEN the char pointer is really the number
     */
    if (OPTST_GET_ARGTYPE(od->fOptState) == OPARG_TYPE_NUMERIC)
        fprintf(fp, "%d", (int)(intptr_t)l_arg);

    else {
        for (;;) {
            char const * eol = strchr(l_arg, NL);

            /*
             *  IF this is the last line
             *  THEN bail and print it
             */
            if (eol == NULL)
                break;

            /*
             *  Print the continuation and the text from the current line
             */
            (void)fwrite(l_arg, (size_t)(eol - l_arg), (size_t)1, fp);
            l_arg = eol+1; /* advance the Last Arg pointer */
            fputs("\\\n", fp);
        }

        /*
         *  Terminate the entry
         */
        fputs(l_arg, fp);
    }

end_entry:
    fputc(NL, fp);
}