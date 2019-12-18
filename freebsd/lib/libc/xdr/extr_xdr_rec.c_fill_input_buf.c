#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_3__ {char* in_base; char* in_boundry; int in_size; int (* readit ) (int /*<<< orphan*/ ,char*,int) ;char* in_finger; int /*<<< orphan*/  tcp_handle; scalar_t__ nonblock; } ;
typedef  TYPE_1__ RECSTREAM ;

/* Variables and functions */
 int BYTES_PER_XDR_UNIT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int stub1 (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool_t  /* knows nothing about records!  Only about input buffers */
fill_input_buf(RECSTREAM *rstrm)
{
	char *where;
	u_int32_t i;
	int len;

	if (rstrm->nonblock)
		return FALSE;

	where = rstrm->in_base;
	i = (u_int32_t)((u_long)rstrm->in_boundry % BYTES_PER_XDR_UNIT);
	where += i;
	len = (u_int32_t)(rstrm->in_size - i);
	if ((len = (*(rstrm->readit))(rstrm->tcp_handle, where, len)) == -1)
		return (FALSE);
	rstrm->in_finger = where;
	where += len;
	rstrm->in_boundry = where;
	return (TRUE);
}