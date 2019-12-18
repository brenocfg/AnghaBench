#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  TYPE_1__* res_state ;
struct TYPE_5__ {unsigned int options; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDB_INTERNAL ; 
 unsigned int RES_INIT ; 
 int /*<<< orphan*/  RES_SET_H_ERRNO (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ _res ; 
 int res_init () ; 
 int res_nmkquery (TYPE_1__*,int,char const*,int,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

int
res_mkquery(int op,			/*!< opcode of query  */
	    const char *dname,		/*!< domain name  */
	    int class, int type,	/*!< class and type of query  */
	    const u_char *data,		/*!< resource record data  */
	    int datalen,		/*!< length of data  */
	    const u_char *newrr_in,	/*!< new rr for modify or append  */
	    u_char *buf,		/*!< buffer to put query  */
	    int buflen)			/*!< size of buffer  */
{
	res_state statp = &_res;
	if ((statp->options & RES_INIT) == 0U && res_init() == -1) {
		RES_SET_H_ERRNO(statp, NETDB_INTERNAL);
		return (-1);
	}
	return (res_nmkquery(statp, op, dname, class, type,
			     data, datalen,
			     newrr_in, buf, buflen));
}