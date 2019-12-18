#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  z ;
struct TYPE_10__ {char* pzProgName; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_11__ {int fOptState; char* pz_Name; scalar_t__ optMinCt; char* pzText; int /*<<< orphan*/ * pOptProc; } ;
typedef  TYPE_2__ tOptDesc ;
struct TYPE_12__ {char* pzOpt; char* pzNo; char* pzKey; char* pzFile; char* pzKeyL; char* pzBool; char* pzNum; char* pzNest; char* pzStr; char* pzTime; char* pzOptFmt; char* pzReq; } ;
typedef  TYPE_3__ arg_types_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_SOFTWARE ; 
#define  OPARG_TYPE_BOOLEAN 136 
#define  OPARG_TYPE_ENUMERATION 135 
#define  OPARG_TYPE_FILE 134 
#define  OPARG_TYPE_HIERARCHY 133 
#define  OPARG_TYPE_MEMBERSHIP 132 
#define  OPARG_TYPE_NONE 131 
#define  OPARG_TYPE_NUMERIC 130 
#define  OPARG_TYPE_STRING 129 
#define  OPARG_TYPE_TIME 128 
 int OPTST_ARG_OPTIONAL ; 
 int OPTST_GET_ARGTYPE (int) ; 
 int displayEnum ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* line_fmt_buf ; 
 int /*<<< orphan*/  option_exits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  option_usage_fp ; 
 int /*<<< orphan*/  prt_preamble (TYPE_1__*,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* zGnuOptFmt ; 
 char* zbad_od ; 

__attribute__((used)) static void
prt_one_usage(tOptions * opts, tOptDesc * od, arg_types_t * at)
{
    prt_preamble(opts, od, at);

    {
        char z[80];
        char const * atyp;

        /*
         *  Determine the argument type string first on its usage, then,
         *  when the option argument is required, base the type string on the
         *  argument type.
         */
        if (od->fOptState & OPTST_ARG_OPTIONAL) {
            atyp = at->pzOpt;

        } else switch (OPTST_GET_ARGTYPE(od->fOptState)) {
        case OPARG_TYPE_NONE:        atyp = at->pzNo;   break;
        case OPARG_TYPE_ENUMERATION: atyp = at->pzKey;  break;
        case OPARG_TYPE_FILE:        atyp = at->pzFile; break;
        case OPARG_TYPE_MEMBERSHIP:  atyp = at->pzKeyL; break;
        case OPARG_TYPE_BOOLEAN:     atyp = at->pzBool; break;
        case OPARG_TYPE_NUMERIC:     atyp = at->pzNum;  break;
        case OPARG_TYPE_HIERARCHY:   atyp = at->pzNest; break;
        case OPARG_TYPE_STRING:      atyp = at->pzStr;  break;
        case OPARG_TYPE_TIME:        atyp = at->pzTime; break;
        default:                     goto bogus_desc;
        }

#ifdef _WIN32
        if (at->pzOptFmt == zGnuOptFmt)
            snprintf(z, sizeof(z), "--%s%s", od->pz_Name, atyp);
        else if (at->pzOptFmt == zGnuOptFmt + 2)
            snprintf(z, sizeof(z), "%s%s", od->pz_Name, atyp);
        else
#endif
        snprintf(z, sizeof(z), at->pzOptFmt, atyp, od->pz_Name,
                 (od->optMinCt != 0) ? at->pzReq : at->pzOpt);

        fprintf(option_usage_fp, line_fmt_buf, z, od->pzText);

        switch (OPTST_GET_ARGTYPE(od->fOptState)) {
        case OPARG_TYPE_ENUMERATION:
        case OPARG_TYPE_MEMBERSHIP:
            displayEnum = (od->pOptProc != NULL) ? true : displayEnum;
        }
    }

    return;

 bogus_desc:
    fprintf(stderr, zbad_od, opts->pzProgName, od->pz_Name);
    option_exits(EX_SOFTWARE);
}