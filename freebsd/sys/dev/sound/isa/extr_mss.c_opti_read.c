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
typedef  int u_char ;
struct mss_info {int password; int bd_id; int /*<<< orphan*/  indir; int /*<<< orphan*/  passwdreg; int /*<<< orphan*/  conf_base; } ;

/* Variables and functions */
#define  MD_OPTI924 129 
#define  MD_OPTI930 128 
 int port_rd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  port_wr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

u_char
opti_read(struct mss_info *mss, u_char reg)
{
	port_wr(mss->conf_base, mss->passwdreg, mss->password);

	switch(mss->bd_id) {
	case MD_OPTI924:
		if (reg > 7) {		/* Indirect register */
			port_wr(mss->conf_base, mss->passwdreg, reg);
			port_wr(mss->conf_base, mss->passwdreg, mss->password);
			return(port_rd(mss->conf_base, 9));
		}
		return(port_rd(mss->conf_base, reg));
		break;

	case MD_OPTI930:
		port_wr(mss->indir, 0, reg);
		port_wr(mss->conf_base, mss->passwdreg, mss->password);
		return port_rd(mss->indir, 1);
		break;
	}
	return -1;
}