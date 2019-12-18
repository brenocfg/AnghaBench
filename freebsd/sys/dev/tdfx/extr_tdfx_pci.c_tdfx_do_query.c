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
struct tdfx_pio_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int _IOC_NR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int tdfx_query_boards () ; 
 int tdfx_query_fetch (int /*<<< orphan*/ ,struct tdfx_pio_data*) ; 
 int tdfx_query_update (int /*<<< orphan*/ ,struct tdfx_pio_data*) ; 

__attribute__((used)) static int
tdfx_do_query(u_int cmd, struct tdfx_pio_data *piod)
{
	/* There are three sub-commands to the query 0x33 */
	switch(_IOC_NR(cmd)) {
		case 2:
			return tdfx_query_boards();
			break;
		case 3:
			return tdfx_query_fetch(cmd, piod);
			break;
		case 4:
			return tdfx_query_update(cmd, piod);
			break;
		default:
			/* In case we are thrown a bogus sub-command! */
#ifdef DEBUG
			printf("Bad Sub-cmd: 0x%x\n", _IOC_NR(cmd));
#endif
			return -EINVAL;
	}
}