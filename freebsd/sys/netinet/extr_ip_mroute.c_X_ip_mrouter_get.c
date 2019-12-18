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
struct sockopt {int sopt_name; } ;
struct socket {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MRT_API_CONFIG 131 
#define  MRT_API_SUPPORT 130 
#define  MRT_ASSERT 129 
#define  MRT_VERSION 128 
 int /*<<< orphan*/  V_mrt_api_config ; 
 int /*<<< orphan*/  V_pim_assert_enabled ; 
 int /*<<< orphan*/  mrt_api_support ; 
 int /*<<< orphan*/  mrt_api_version ; 
 int sooptcopyout (struct sockopt*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
X_ip_mrouter_get(struct socket *so, struct sockopt *sopt)
{
    int error;

    switch (sopt->sopt_name) {
    case MRT_VERSION:
	error = sooptcopyout(sopt, &mrt_api_version, sizeof mrt_api_version);
	break;

    case MRT_ASSERT:
	error = sooptcopyout(sopt, &V_pim_assert_enabled,
	    sizeof V_pim_assert_enabled);
	break;

    case MRT_API_SUPPORT:
	error = sooptcopyout(sopt, &mrt_api_support, sizeof mrt_api_support);
	break;

    case MRT_API_CONFIG:
	error = sooptcopyout(sopt, &V_mrt_api_config, sizeof V_mrt_api_config);
	break;

    default:
	error = EOPNOTSUPP;
	break;
    }
    return error;
}