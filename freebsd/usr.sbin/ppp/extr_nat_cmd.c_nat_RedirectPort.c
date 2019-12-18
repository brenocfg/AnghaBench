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
typedef  scalar_t__ u_short ;
struct in_addr {void* s_addr; } ;
struct cmdargs {int argc; int argn; char** argv; int /*<<< orphan*/  prompt; TYPE_1__* bundle; } ;
struct alias_link {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  NatEnabled; } ;

/* Variables and functions */
 void* INADDR_ANY ; 
 char IPPROTO_TCP ; 
 char IPPROTO_UDP ; 
 struct alias_link* LibAliasRedirectPort (int /*<<< orphan*/ ,struct in_addr,int /*<<< orphan*/ ,struct in_addr,int /*<<< orphan*/ ,struct in_addr,int /*<<< orphan*/ ,char) ; 
 int StrToAddrAndPort (char*,struct in_addr*,scalar_t__*,scalar_t__*,char const*) ; 
 int StrToPortRange (char*,scalar_t__*,scalar_t__*,char const*) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  la ; 
 int /*<<< orphan*/  lowhigh (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  prompt_Printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int
nat_RedirectPort(struct cmdargs const *arg)
{
  if (!arg->bundle->NatEnabled) {
    prompt_Printf(arg->prompt, "Alias not enabled\n");
    return 1;
  } else if (arg->argc == arg->argn + 3 || arg->argc == arg->argn + 4) {
    char proto_constant;
    const char *proto;
    struct in_addr localaddr;
    u_short hlocalport, llocalport;
    struct in_addr aliasaddr;
    u_short haliasport, laliasport;
    struct in_addr remoteaddr;
    u_short hremoteport, lremoteport;
    struct alias_link *link;
    int error;

    proto = arg->argv[arg->argn];
    if (strcmp(proto, "tcp") == 0) {
      proto_constant = IPPROTO_TCP;
    } else if (strcmp(proto, "udp") == 0) {
      proto_constant = IPPROTO_UDP;
    } else {
      prompt_Printf(arg->prompt, "port redirect: protocol must be"
                    " tcp or udp\n");
      return -1;
    }

    error = StrToAddrAndPort(arg->argv[arg->argn+1], &localaddr, &llocalport,
                             &hlocalport, proto);
    if (error) {
      prompt_Printf(arg->prompt, "nat port: error reading localaddr:port\n");
      return -1;
    }

    error = StrToPortRange(arg->argv[arg->argn+2], &laliasport, &haliasport,
                           proto);
    if (error) {
      prompt_Printf(arg->prompt, "nat port: error reading alias port\n");
      return -1;
    }
    aliasaddr.s_addr = INADDR_ANY;

    if (arg->argc == arg->argn + 4) {
      error = StrToAddrAndPort(arg->argv[arg->argn+3], &remoteaddr,
                               &lremoteport, &hremoteport, proto);
      if (error) {
        prompt_Printf(arg->prompt, "nat port: error reading "
                      "remoteaddr:port\n");
        return -1;
      }
    } else {
      remoteaddr.s_addr = INADDR_ANY;
      lremoteport = hremoteport = 0;
    }

    lowhigh(&llocalport, &hlocalport);
    lowhigh(&laliasport, &haliasport);
    lowhigh(&lremoteport, &hremoteport);

    if (haliasport - laliasport != hlocalport - llocalport) {
      prompt_Printf(arg->prompt, "nat port: local & alias port ranges "
                    "are not equal\n");
      return -1;
    }

    if (hremoteport && hremoteport - lremoteport != hlocalport - llocalport) {
      prompt_Printf(arg->prompt, "nat port: local & remote port ranges "
                    "are not equal\n");
      return -1;
    }

    do {
      link = LibAliasRedirectPort(la, localaddr, htons(llocalport),
				     remoteaddr, htons(lremoteport),
                                     aliasaddr, htons(laliasport),
				     proto_constant);

      if (link == NULL) {
        prompt_Printf(arg->prompt, "nat port: %d: error %d\n", laliasport,
                      error);
        return 1;
      }
      llocalport++;
      if (hremoteport)
        lremoteport++;
    } while (laliasport++ < haliasport);

    return 0;
  }

  return -1;
}