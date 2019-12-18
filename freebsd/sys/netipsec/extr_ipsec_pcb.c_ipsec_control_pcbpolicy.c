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
struct sockopt {size_t sopt_valsize; scalar_t__ sopt_dir; TYPE_1__* sopt_td; } ;
struct sadb_x_policy {int dummy; } ;
struct inpcb {int /*<<< orphan*/ * inp_sp; } ;
struct TYPE_2__ {int /*<<< orphan*/ * td_ucred; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 size_t PAGE_SIZE ; 
 scalar_t__ SOPT_SET ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int ipsec_get_pcbpolicy (struct inpcb*,void*,size_t*) ; 
 int ipsec_set_pcbpolicy (struct inpcb*,int /*<<< orphan*/ *,void*,size_t) ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sooptcopyin (struct sockopt*,void*,size_t,size_t) ; 
 int sooptcopyout (struct sockopt*,void*,size_t) ; 

__attribute__((used)) static int
ipsec_control_pcbpolicy(struct inpcb *inp, struct sockopt *sopt)
{
	void *optdata;
	size_t optlen;
	int error;

	if (inp->inp_sp == NULL)
		return (ENOPROTOOPT);

	/* Limit maximum request size to PAGE_SIZE */
	optlen = sopt->sopt_valsize;
	if (optlen < sizeof(struct sadb_x_policy) || optlen > PAGE_SIZE)
		return (EINVAL);

	optdata = malloc(optlen, M_TEMP, sopt->sopt_td ? M_WAITOK: M_NOWAIT);
	if (optdata == NULL)
		return (ENOBUFS);
	/*
	 * We need a hint from the user, what policy is requested - input
	 * or output? User should specify it in the buffer, even for
	 * setsockopt().
	 */
	error = sooptcopyin(sopt, optdata, optlen, optlen);
	if (error == 0) {
		if (sopt->sopt_dir == SOPT_SET)
			error = ipsec_set_pcbpolicy(inp,
			    sopt->sopt_td ? sopt->sopt_td->td_ucred: NULL,
			    optdata, optlen);
		else {
			error = ipsec_get_pcbpolicy(inp, optdata, &optlen);
			if (error == 0)
				error = sooptcopyout(sopt, optdata, optlen);
		}
	}
	free(optdata, M_TEMP);
	return (error);
}