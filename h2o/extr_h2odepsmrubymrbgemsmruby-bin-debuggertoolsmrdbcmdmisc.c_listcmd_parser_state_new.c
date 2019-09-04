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
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  listcmd_parser_state ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static listcmd_parser_state*
listcmd_parser_state_new(mrb_state *mrb)
{
  listcmd_parser_state *st = (listcmd_parser_state*)mrb_malloc(mrb, sizeof(listcmd_parser_state));
  memset(st, 0, sizeof(listcmd_parser_state));
  return st;
}