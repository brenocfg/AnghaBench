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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct ngdevice {TYPE_1__ dev; int /*<<< orphan*/  cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogWARN ; 
 int NG_PATHSIZ ; 
 scalar_t__ NgSendAsciiMsg (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 char* alloca (size_t) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strspn (char const*,char*) ; 

__attribute__((used)) static int
ng_MessageOut(struct ngdevice *dev, const char *data)
{
  char path[NG_PATHSIZ];
  char *fmt;
  size_t len;
  int pos, dpos;

  /*
   * We expect a node path, one or more spaces, a command, one or more
   * spaces and an ascii netgraph structure.
   */
  data += strspn(data, " \t");
  len = strcspn(data, " \t");
  if (len >= sizeof path) {
    log_Printf(LogWARN, "%s: %.*s: Node path too long\n",
                 dev->dev.name, len, data);
    return 0;
  }
  memcpy(path, data, len);
  path[len] = '\0';
  data += len;

  data += strspn(data, " \t");
  len = strcspn(data, " \t");
  for (pos = len; pos >= 0; pos--)
    if (data[pos] == '%')
      len++;
  if ((fmt = alloca(len + 4)) == NULL) {
    log_Printf(LogWARN, "%s: alloca(%d) failure... %s\n",
               dev->dev.name, len + 4, strerror(errno));
    return 0;
  }

  /*
   * This is probably a waste of time, but we really don't want to end
   * up stuffing unexpected % escapes into the kernel....
   */
  for (pos = dpos = 0; pos < (int)len;) {
    if (data[dpos] == '%')
      fmt[pos++] = '%';
    fmt[pos++] = data[dpos++];
  }
  strcpy(fmt + pos, " %s");
  data += dpos;

  data += strspn(data, " \t");
  if (NgSendAsciiMsg(dev->cs, path, fmt, data) < 0) {
    log_Printf(LogDEBUG, "%s: NgSendAsciiMsg (to %s): \"%s\", \"%s\": %s\n",
               dev->dev.name, path, fmt, data, strerror(errno));
    return 0;
  }

  return 1;
}