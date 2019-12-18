#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct physical {int dummy; } ;
struct TYPE_6__ {char* local; char* peer; } ;
struct TYPE_5__ {int fd; scalar_t__ pid; } ;
struct TYPE_4__ {int /*<<< orphan*/  Write; int /*<<< orphan*/  Read; int /*<<< orphan*/  IsSet; int /*<<< orphan*/  UpdateSet; int /*<<< orphan*/  type; } ;
struct chap {scalar_t__ peertries; scalar_t__ NTRespSent; TYPE_3__ challenge; int /*<<< orphan*/  auth; TYPE_2__ child; TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAP_DESCRIPTOR ; 
 int /*<<< orphan*/  auth_Init (int /*<<< orphan*/ *,struct physical*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chap_Challenge ; 
 int /*<<< orphan*/  chap_Failure ; 
 int /*<<< orphan*/  chap_IsSet ; 
 int /*<<< orphan*/  chap_Read ; 
 int /*<<< orphan*/  chap_Success ; 
 int /*<<< orphan*/  chap_UpdateSet ; 
 int /*<<< orphan*/  chap_Write ; 

void
chap_Init(struct chap *chap, struct physical *p)
{
  chap->desc.type = CHAP_DESCRIPTOR;
  chap->desc.UpdateSet = chap_UpdateSet;
  chap->desc.IsSet = chap_IsSet;
  chap->desc.Read = chap_Read;
  chap->desc.Write = chap_Write;
  chap->child.pid = 0;
  chap->child.fd = -1;
  auth_Init(&chap->auth, p, chap_Challenge, chap_Success, chap_Failure);
  *chap->challenge.local = *chap->challenge.peer = '\0';
#ifndef NODES
  chap->NTRespSent = 0;
  chap->peertries = 0;
#endif
}