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
struct svc_req {int /*<<< orphan*/  rq_xprt; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  VIS_WHITE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  from_addr (struct sockaddr*) ; 
 char* malloc (int) ; 
 int strlen (char*) ; 
 int strvis (char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svc_getrpccaller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 

int sm_check_hostname(struct svc_req *req, char *arg)
{
  int len, dstlen, ret;
  struct sockaddr *claddr;
  char *dst;

  len = strlen(arg);
  dstlen = (4 * len) + 1;
  dst = malloc(dstlen);
  claddr = (struct sockaddr *) (svc_getrpccaller(req->rq_xprt)->buf) ;
  ret = 1;

  if (claddr == NULL || dst == NULL)
  {
    ret = 0;
  }
  else if (strvis(dst, arg, VIS_WHITE) != len)
  {
    syslog(LOG_ERR,
	"sm_stat: client %s hostname %s contained invalid characters.",
	from_addr(claddr),
	dst);
    ret = 0;
  }
  free(dst);
  return (ret);
}