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
typedef  int /*<<< orphan*/  u_short ;

/* Variables and functions */
#define  OP_EQ 130 
#define  OP_GT 129 
#define  OP_LT 128 

__attribute__((used)) static __inline int
PortMatch(int op, u_short pport, u_short rport)
{
  switch (op) {
  case OP_EQ:
    return pport == rport;
  case OP_GT:
    return pport > rport;
  case OP_LT:
    return pport < rport;
  default:
    return 0;
  }
}