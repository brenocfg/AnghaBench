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
struct mbchain {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MB_MUSER ; 
 int mb_init (struct mbchain*) ; 
 int mb_put_mem (struct mbchain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smb_cpdatain(struct mbchain *mbp, int len, caddr_t data)
{
	int error;

	if (len == 0)
		return 0;
	error = mb_init(mbp);
	if (error)
		return error;
	return mb_put_mem(mbp, data, len, MB_MUSER);
}