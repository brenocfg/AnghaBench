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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseSecret (int /*<<< orphan*/ *) ; 
 int LINE_LEN ; 
 int /*<<< orphan*/  LogWARN ; 
 int MakeArgs (char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenSecret (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_REDUCE ; 
 int /*<<< orphan*/  SECRETFILE ; 
 int /*<<< orphan*/  VECSIZE (char**) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (char**,char,int) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strrchr (char const*,char) ; 

int
auth_SetPhoneList(const char *name, char *phone, int phonelen)
{
  FILE *fp;
  int n, lineno;
  char *vector[6], buff[LINE_LEN];
  const char *slash;

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
      if (n < 5)
        continue;
      if (strcmp(vector[0], name) == 0) {
        CloseSecret(fp);
        if (*vector[4] == '\0')
          return 0;
        strncpy(phone, vector[4], phonelen - 1);
        phone[phonelen - 1] = '\0';
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
  *phone = '\0';
  return 0;
}