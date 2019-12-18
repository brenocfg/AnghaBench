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
struct cmdtab {int lauth; } ;

/* Variables and functions */
 int LOCAL_CX ; 
 int LOCAL_CX_OPT ; 

__attribute__((used)) static const char *
showcx(struct cmdtab const *cmd)
{
  if (cmd->lauth & LOCAL_CX)
    return "(c)";
  else if (cmd->lauth & LOCAL_CX_OPT)
    return "(o)";

  return "";
}