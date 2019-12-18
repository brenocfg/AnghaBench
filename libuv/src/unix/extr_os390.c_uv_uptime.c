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
typedef  int /*<<< orphan*/  time64_t ;
struct TYPE_2__ {int /*<<< orphan*/  tv_sec; } ;
struct utmpx {TYPE_1__ ut_tv; int /*<<< orphan*/  ut_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOT_TIME ; 
 double difftime64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct utmpx* getutxid (struct utmpx*) ; 
 int /*<<< orphan*/  time64 (int /*<<< orphan*/ *) ; 

int uv_uptime(double* uptime) {
  struct utmpx u ;
  struct utmpx *v;
  time64_t t;

  u.ut_type = BOOT_TIME;
  v = getutxid(&u);
  if (v == NULL)
    return -1;
  *uptime = difftime64(time64(&t), v->ut_tv.tv_sec);
  return 0;
}