#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  ruid; int /*<<< orphan*/  rgid; int /*<<< orphan*/  egid; int /*<<< orphan*/  euid; int /*<<< orphan*/  auid; } ;
struct TYPE_6__ {TYPE_1__ proc32; } ;
struct TYPE_7__ {TYPE_2__ tt; } ;
typedef  TYPE_3__ tokenstr_t ;

/* Variables and functions */
 int OPT_e ; 
 int OPT_f ; 
 int OPT_g ; 
 int OPT_op ; 
 int OPT_r ; 
 int OPT_u ; 
 int /*<<< orphan*/  SETOPT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  select_auid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_egid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_euid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_pidobj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_rgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_ruid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
select_proc32(tokenstr_t tok, uint32_t *optchkd)
{

	SETOPT((*optchkd), (OPT_u | OPT_e | OPT_f | OPT_g | OPT_r | OPT_op));

	if (!select_auid(tok.tt.proc32.auid))
		return (0);
	if (!select_euid(tok.tt.proc32.euid))
		return (0);
	if (!select_egid(tok.tt.proc32.egid))
		return (0);
	if (!select_rgid(tok.tt.proc32.rgid))
		return (0);
	if (!select_ruid(tok.tt.proc32.ruid))
		return (0);
	if (!select_pidobj(tok.tt.proc32.pid))
		return (0);
	return (1);
}