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
struct sockopt {int sopt_valsize; int sopt_dir; } ;
struct newreno {int /*<<< orphan*/  beta_ecn; int /*<<< orphan*/  beta; } ;
struct cc_var {struct newreno* cc_data; } ;
struct cc_newreno_opts {int /*<<< orphan*/  val; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  CC_NEWRENO_BETA 131 
#define  CC_NEWRENO_BETA_ECN 130 
 int EACCES ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int ENOPROTOOPT ; 
#define  SOPT_GET 129 
#define  SOPT_SET 128 
 int /*<<< orphan*/  V_cc_do_abe ; 
 int /*<<< orphan*/  V_newreno_beta ; 
 int /*<<< orphan*/  V_newreno_beta_ecn ; 
 struct newreno* newreno_malloc (struct cc_var*) ; 

__attribute__((used)) static int
newreno_ctl_output(struct cc_var *ccv, struct sockopt *sopt, void *buf)
{
	struct newreno *nreno;
	struct cc_newreno_opts *opt;

	if (sopt->sopt_valsize != sizeof(struct cc_newreno_opts))
		return (EMSGSIZE);

	nreno = ccv->cc_data;
	opt = buf;

	switch (sopt->sopt_dir) {
	case SOPT_SET:
		/* We cannot set without cc_data memory. */
		if (nreno == NULL) {
			nreno = newreno_malloc(ccv);
			if (nreno == NULL)
				return (ENOMEM);
		}
		switch (opt->name) {
		case CC_NEWRENO_BETA:
			nreno->beta = opt->val;
			break;
		case CC_NEWRENO_BETA_ECN:
			if (!V_cc_do_abe)
				return (EACCES);
			nreno->beta_ecn = opt->val;
			break;
		default:
			return (ENOPROTOOPT);
		}
		break;
	case SOPT_GET:
		switch (opt->name) {
		case CC_NEWRENO_BETA:
			opt->val = (nreno == NULL) ?
			    V_newreno_beta : nreno->beta;
			break;
		case CC_NEWRENO_BETA_ECN:
			opt->val = (nreno == NULL) ?
			    V_newreno_beta_ecn : nreno->beta_ecn;
			break;
		default:
			return (ENOPROTOOPT);
		}
		break;
	default:
		return (EINVAL);
	}

	return (0);
}