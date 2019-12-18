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
struct authinfo {TYPE_1__* physical; } ;
struct TYPE_2__ {int /*<<< orphan*/  dl; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAP_NAK ; 
 int /*<<< orphan*/  SendPapCode (struct authinfo*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  datalink_AuthNotOk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pap_Failure(struct authinfo *authp)
{
  SendPapCode(authp, PAP_NAK, "Login incorrect");
  datalink_AuthNotOk(authp->physical->dl);
}