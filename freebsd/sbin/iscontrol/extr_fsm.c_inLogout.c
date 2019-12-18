#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trans_t ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ isess_t ;

/* Variables and functions */
 int SESS_RECONNECT ; 
 int /*<<< orphan*/  T18 ; 

__attribute__((used)) static trans_t
inLogout(isess_t *sess)
{
     if(sess->flags & SESS_RECONNECT)
	  return T18;
     return 0;
}