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
typedef  int /*<<< orphan*/  u_int ;
struct ng_mesg {int dummy; } ;
typedef  int ng_ID_t ;

/* Variables and functions */
 int NG_PATHSIZ ; 
 struct ng_mesg* ng_dialog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

struct ng_mesg *
ng_dialog_id(ng_ID_t id, u_int cookie, u_int opcode,
    const void *arg, size_t arglen)
{
	char path[NG_PATHSIZ];

	sprintf(path, "[%x]:", id);
	return (ng_dialog(path, cookie, opcode, arg, arglen));
}