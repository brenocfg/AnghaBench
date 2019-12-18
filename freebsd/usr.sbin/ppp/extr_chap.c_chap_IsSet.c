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
struct fdescriptor {int dummy; } ;
struct TYPE_2__ {int fd; } ;
struct chap {TYPE_1__ child; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/  const*) ; 
 struct chap* descriptor2chap (struct fdescriptor*) ; 

__attribute__((used)) static int
chap_IsSet(struct fdescriptor *d, const fd_set *fdset)
{
  struct chap *chap = descriptor2chap(d);

  return chap && chap->child.fd != -1 && FD_ISSET(chap->child.fd, fdset);
}