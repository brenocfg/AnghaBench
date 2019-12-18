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
typedef  int u32 ;
struct mlx5e_eth_addr_info {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
#define  MLX5E_ALLMULTI 132 
#define  MLX5E_FULLMATCH 131 
#define  MLX5E_MC_IPV4 130 
#define  MLX5E_MC_IPV6 129 
 int MLX5E_TT_ANY ; 
 int MLX5E_TT_IPV4 ; 
 int MLX5E_TT_IPV4_TCP ; 
 int MLX5E_TT_IPV4_UDP ; 
 int MLX5E_TT_IPV6 ; 
 int MLX5E_TT_IPV6_TCP ; 
 int MLX5E_TT_IPV6_UDP ; 
#define  MLX5E_UC 128 
 int mlx5e_get_eth_addr_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static	u32
mlx5e_get_tt_vec(struct mlx5e_eth_addr_info *ai, int type)
{
	int eth_addr_type;
	u32 ret;

	switch (type) {
	case MLX5E_FULLMATCH:
		eth_addr_type = mlx5e_get_eth_addr_type(ai->addr);
		switch (eth_addr_type) {
		case MLX5E_UC:
			ret =
			    (1 << MLX5E_TT_IPV4_TCP) |
			    (1 << MLX5E_TT_IPV6_TCP) |
			    (1 << MLX5E_TT_IPV4_UDP) |
			    (1 << MLX5E_TT_IPV6_UDP) |
			    (1 << MLX5E_TT_IPV4) |
			    (1 << MLX5E_TT_IPV6) |
			    (1 << MLX5E_TT_ANY) |
			    0;
			break;

		case MLX5E_MC_IPV4:
			ret =
			    (1 << MLX5E_TT_IPV4_UDP) |
			    (1 << MLX5E_TT_IPV4) |
			    0;
			break;

		case MLX5E_MC_IPV6:
			ret =
			    (1 << MLX5E_TT_IPV6_UDP) |
			    (1 << MLX5E_TT_IPV6) |
			    0;
			break;

		default:
			ret =
			    (1 << MLX5E_TT_ANY) |
			    0;
			break;
		}
		break;

	case MLX5E_ALLMULTI:
		ret =
		    (1 << MLX5E_TT_IPV4_UDP) |
		    (1 << MLX5E_TT_IPV6_UDP) |
		    (1 << MLX5E_TT_IPV4) |
		    (1 << MLX5E_TT_IPV6) |
		    (1 << MLX5E_TT_ANY) |
		    0;
		break;

	default:			/* MLX5E_PROMISC */
		ret =
		    (1 << MLX5E_TT_IPV4_TCP) |
		    (1 << MLX5E_TT_IPV6_TCP) |
		    (1 << MLX5E_TT_IPV4_UDP) |
		    (1 << MLX5E_TT_IPV6_UDP) |
		    (1 << MLX5E_TT_IPV4) |
		    (1 << MLX5E_TT_IPV6) |
		    (1 << MLX5E_TT_ANY) |
		    0;
		break;
	}

	return (ret);
}