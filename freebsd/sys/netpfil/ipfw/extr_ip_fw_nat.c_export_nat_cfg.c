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
struct nat44_cfg_nat {int /*<<< orphan*/  if_name; int /*<<< orphan*/  mode; int /*<<< orphan*/  redir_cnt; int /*<<< orphan*/  ip; int /*<<< orphan*/  name; } ;
struct cfg_nat {int id; int /*<<< orphan*/  if_name; int /*<<< orphan*/  mode; int /*<<< orphan*/  redir_cnt; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
export_nat_cfg(struct cfg_nat *ptr, struct nat44_cfg_nat *ucfg)
{

	snprintf(ucfg->name, sizeof(ucfg->name), "%d", ptr->id);
	ucfg->ip = ptr->ip;
	ucfg->redir_cnt = ptr->redir_cnt;
	ucfg->mode = ptr->mode;
	strlcpy(ucfg->if_name, ptr->if_name, sizeof(ucfg->if_name));
}