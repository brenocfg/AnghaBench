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
struct ncpaddr {int dummy; } ;
struct in_addr {int dummy; } ;
struct filterent {scalar_t__ f_action; scalar_t__ f_srctype; scalar_t__ f_dsttype; int /*<<< orphan*/  f_dst; int /*<<< orphan*/  f_src; } ;
struct filter {struct filterent* rule; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ A_NONE ; 
 int MAXFILTERS ; 
 scalar_t__ T_DNS0 ; 
 scalar_t__ T_DNS1 ; 
 scalar_t__ T_HISADDR ; 
 scalar_t__ T_HISADDR6 ; 
 scalar_t__ T_MYADDR ; 
 scalar_t__ T_MYADDR6 ; 
 scalar_t__ ncpaddr_family (struct ncpaddr*) ; 
 int /*<<< orphan*/  ncprange_sethost (int /*<<< orphan*/ *,struct ncpaddr*) ; 
 int /*<<< orphan*/  ncprange_setip4host (int /*<<< orphan*/ *,struct in_addr) ; 

void
filter_AdjustAddr(struct filter *filter, struct ncpaddr *local,
                  struct ncpaddr *remote, struct in_addr *dns)
{
  struct filterent *fp;
  int n;

  for (fp = filter->rule, n = 0; n < MAXFILTERS; fp++, n++)
    if (fp->f_action != A_NONE) {
      if (local) {
        if (fp->f_srctype == T_MYADDR && ncpaddr_family(local) == AF_INET)
          ncprange_sethost(&fp->f_src, local);
        if (fp->f_dsttype == T_MYADDR && ncpaddr_family(local) == AF_INET)
          ncprange_sethost(&fp->f_dst, local);
#ifndef NOINET6
        if (fp->f_srctype == T_MYADDR6 && ncpaddr_family(local) == AF_INET6)
          ncprange_sethost(&fp->f_src, local);
        if (fp->f_dsttype == T_MYADDR6 && ncpaddr_family(local) == AF_INET6)
          ncprange_sethost(&fp->f_dst, local);
#endif
      }
      if (remote) {
        if (fp->f_srctype == T_HISADDR && ncpaddr_family(remote) == AF_INET)
          ncprange_sethost(&fp->f_src, remote);
        if (fp->f_dsttype == T_HISADDR && ncpaddr_family(remote) == AF_INET)
          ncprange_sethost(&fp->f_dst, remote);
#ifndef NOINET6
        if (fp->f_srctype == T_HISADDR6 && ncpaddr_family(remote) == AF_INET6)
          ncprange_sethost(&fp->f_src, remote);
        if (fp->f_dsttype == T_HISADDR6 && ncpaddr_family(remote) == AF_INET6)
          ncprange_sethost(&fp->f_dst, remote);
#endif
      }
      if (dns) {
        if (fp->f_srctype == T_DNS0)
          ncprange_setip4host(&fp->f_src, dns[0]);
        if (fp->f_dsttype == T_DNS0)
          ncprange_setip4host(&fp->f_dst, dns[0]);
        if (fp->f_srctype == T_DNS1)
          ncprange_setip4host(&fp->f_src, dns[1]);
        if (fp->f_dsttype == T_DNS1)
          ncprange_setip4host(&fp->f_dst, dns[1]);
      }
    }
}