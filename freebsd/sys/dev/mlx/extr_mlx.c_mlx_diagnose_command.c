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
struct mlx_command {int* mc_mailbox; scalar_t__ mc_status; } ;
struct TYPE_2__ {int command; scalar_t__ status; size_t msg; } ;

/* Variables and functions */
 TYPE_1__* mlx_messages ; 
 char** mlx_status_messages ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static char *
mlx_diagnose_command(struct mlx_command *mc)
{
    static char	unkmsg[80];
    int		i;
    
    /* look up message in table */
    for (i = 0; mlx_messages[i].command != -1; i++)
	if (((mc->mc_mailbox[0] == mlx_messages[i].command) || (mlx_messages[i].command == 0)) &&
	    (mc->mc_status == mlx_messages[i].status))
	    return(mlx_status_messages[mlx_messages[i].msg]);
	
    sprintf(unkmsg, "unknown response 0x%x for command 0x%x", (int)mc->mc_status, (int)mc->mc_mailbox[0]);
    return(unkmsg);
}