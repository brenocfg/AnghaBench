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
struct physical {int dummy; } ;
struct authinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_Init (struct authinfo*,struct physical*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pap_Failure ; 
 int /*<<< orphan*/  pap_Req ; 
 int /*<<< orphan*/  pap_Success ; 

void
pap_Init(struct authinfo *pap, struct physical *p)
{
  auth_Init(pap, p, pap_Req, pap_Success, pap_Failure);
}