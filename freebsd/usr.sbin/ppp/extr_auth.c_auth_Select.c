#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ s_addr; } ;
struct TYPE_5__ {scalar_t__ s_addr; } ;
struct TYPE_7__ {scalar_t__ valid; TYPE_4__ ip; TYPE_1__ mask; } ;
struct TYPE_6__ {int /*<<< orphan*/  ipcp; } ;
struct bundle {TYPE_3__ radius; TYPE_2__ ncp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseSecret (int /*<<< orphan*/ *) ; 
 scalar_t__ INADDR_NONE ; 
 int LINE_LEN ; 
 int /*<<< orphan*/  LogWARN ; 
 int MakeArgs (char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenSecret (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_REDUCE ; 
 scalar_t__ RADIUS_INADDR_POOL ; 
 int /*<<< orphan*/  SECRETFILE ; 
 int /*<<< orphan*/  VECSIZE (char**) ; 
 int /*<<< orphan*/  bundle_SetLabel (struct bundle*,char*) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipcp_Setup (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ipcp_UseHisIPaddr (struct bundle*,TYPE_4__) ; 
 int /*<<< orphan*/  ipcp_UseHisaddr (struct bundle*,char*,int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (char**,char,int) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char*) ; 
 char* strrchr (char const*,char) ; 

int
auth_Select(struct bundle *bundle, const char *name)
{
  FILE *fp;
  int n, lineno;
  char *vector[5], buff[LINE_LEN];
  const char *slash;

  if (*name == '\0') {
    ipcp_Setup(&bundle->ncp.ipcp, INADDR_NONE);
    return 1;
  }

#ifndef NORADIUS
  if (bundle->radius.valid && bundle->radius.ip.s_addr != INADDR_NONE &&
	bundle->radius.ip.s_addr != RADIUS_INADDR_POOL) {
    /* We've got a radius IP - it overrides everything */
    if (!ipcp_UseHisIPaddr(bundle, bundle->radius.ip))
      return 0;
    ipcp_Setup(&bundle->ncp.ipcp, bundle->radius.mask.s_addr);
    /* Continue with ppp.secret in case we've got a new label */
  }
#endif

  fp = OpenSecret(SECRETFILE);
  if (fp != NULL) {
again:
    lineno = 0;
    while (fgets(buff, sizeof buff, fp)) {
      lineno++;
      if (buff[0] == '#')
        continue;
      buff[strlen(buff) - 1] = '\0';
      memset(vector, '\0', sizeof vector);
      if ((n = MakeArgs(buff, vector, VECSIZE(vector), PARSE_REDUCE)) < 0)
        log_Printf(LogWARN, "%s: %d: Invalid line\n", SECRETFILE, lineno);
      if (n < 2)
        continue;
      if (strcmp(vector[0], name) == 0) {
        CloseSecret(fp);
#ifndef NORADIUS
        if (!bundle->radius.valid || bundle->radius.ip.s_addr == INADDR_NONE) {
#endif
          if (n > 2 && *vector[2] && strcmp(vector[2], "*") &&
              !ipcp_UseHisaddr(bundle, vector[2], 1))
            return 0;
          ipcp_Setup(&bundle->ncp.ipcp, INADDR_NONE);
#ifndef NORADIUS
        }
#endif
        if (n > 3 && *vector[3] && strcmp(vector[3], "*"))
          bundle_SetLabel(bundle, vector[3]);
        return 1;		/* Valid */
      }
    }

    if ((slash = strrchr(name, '\\')) != NULL && slash[1]) {
      /* Look for the name without the leading domain */
      name = slash + 1;
      rewind(fp);
      goto again;
    }

    CloseSecret(fp);
  }

#ifndef NOPASSWDAUTH
  /* Let 'em in anyway - they must have been in the passwd file */
  ipcp_Setup(&bundle->ncp.ipcp, INADDR_NONE);
  return 1;
#else
#ifndef NORADIUS
  if (bundle->radius.valid)
    return 1;
#endif

  /* Disappeared from ppp.secret ??? */
  return 0;
#endif
}