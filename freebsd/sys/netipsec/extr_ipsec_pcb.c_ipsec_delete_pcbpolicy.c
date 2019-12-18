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
struct inpcb {TYPE_1__* inp_sp; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sp_out; int /*<<< orphan*/ * sp_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPSEC_INPCB ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_freesp (int /*<<< orphan*/ **) ; 

int
ipsec_delete_pcbpolicy(struct inpcb *inp)
{

	if (inp->inp_sp == NULL)
		return (0);

	if (inp->inp_sp->sp_in != NULL)
		key_freesp(&inp->inp_sp->sp_in);

	if (inp->inp_sp->sp_out != NULL)
		key_freesp(&inp->inp_sp->sp_out);

	free(inp->inp_sp, M_IPSEC_INPCB);
	inp->inp_sp = NULL;
	return (0);
}