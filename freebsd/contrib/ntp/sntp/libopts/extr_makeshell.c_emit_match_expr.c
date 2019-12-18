#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int optCt; TYPE_2__* pOptDesc; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_7__ {char const* pz_Name; scalar_t__* pz_DisableName; } ;
typedef  TYPE_2__ tOptDesc ;
typedef  int /*<<< orphan*/  name_bf ;

/* Variables and functions */
 char const NUL ; 
 scalar_t__ SKIP_OPT (TYPE_2__*) ; 
 scalar_t__ UPPER (char const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ toupper (unsigned char) ; 
 char* zOptionFullName ; 
 char* zOptionPartName ; 

__attribute__((used)) static void
emit_match_expr(char const * name, tOptDesc * cod, tOptions * opts)
{
    char name_bf[32];
    unsigned int    min_match_ct = 2;
    unsigned int    max_match_ct = strlen(name) - 1;

    if (max_match_ct >= sizeof(name_bf) - 1)
        goto leave;
    
    {
        tOptDesc *  od = opts->pOptDesc;
        int         ct = opts->optCt;

        for (; ct-- > 0; od++) {
            unsigned int match_ct = 0;

            /*
             *  Omit the current option, Doc opts and compiled out opts.
             */
            if ((od == cod) || SKIP_OPT(od))
                continue;

            /*
             *  Check each character of the name case insensitively.
             *  They must not be the same.  They cannot be, because it would
             *  not compile correctly if they were.
             */
            while (UPPER(od->pz_Name[match_ct]) == UPPER(name[match_ct]))
                match_ct++;

            if (match_ct > min_match_ct)
                min_match_ct = match_ct;

            /*
             *  Check the disablement name, too.
             */
            if (od->pz_DisableName == NULL)
                continue;

            match_ct = 0;
            while (  toupper((unsigned char)od->pz_DisableName[match_ct])
                  == toupper((unsigned char)name[match_ct]))
                match_ct++;
            if (match_ct > min_match_ct)
                min_match_ct = match_ct;
        }
    }

    /*
     *  Don't bother emitting partial matches if there is only one possible
     *  partial match.
     */
    if (min_match_ct < max_match_ct) {
        char *  pz    = name_bf + min_match_ct;
        int     nm_ix = min_match_ct;

        memcpy(name_bf, name, min_match_ct);

        for (;;) {
            *pz = NUL;
            printf(zOptionPartName, name_bf);
            *pz++ = name[nm_ix++];
            if (name[nm_ix] == NUL) {
                *pz = NUL;
                break;
            }
        }
    }

leave:
    printf(zOptionFullName, name);
}