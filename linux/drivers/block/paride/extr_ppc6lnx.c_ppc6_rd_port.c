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
typedef  int u8 ;
typedef  int /*<<< orphan*/  Interface ;

/* Variables and functions */
 int ACCESS_PORT ; 
 int ACCESS_READ ; 
 int ppc6_rd_data_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppc6_send_cmd (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u8 ppc6_rd_port(Interface *ppc, u8 port)
{
	ppc6_send_cmd(ppc,(u8)(port | ACCESS_PORT | ACCESS_READ));

	return(ppc6_rd_data_byte(ppc));
}