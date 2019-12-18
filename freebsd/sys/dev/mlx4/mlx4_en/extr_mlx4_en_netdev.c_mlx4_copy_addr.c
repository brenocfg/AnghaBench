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
typedef  int u_int ;
struct sockaddr_dl {scalar_t__ sdl_alen; } ;
struct mlx4_en_priv {int /*<<< orphan*/  uc_list; } ;
struct mlx4_en_addr_list {int /*<<< orphan*/  list; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 struct mlx4_en_addr_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int mlx4_copy_addr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct mlx4_en_priv *priv = arg;
	struct mlx4_en_addr_list *tmp;

	if (sdl->sdl_alen != ETHER_ADDR_LEN)	/* XXXGL: can that happen? */
		return (0);
	tmp = kzalloc(sizeof(struct mlx4_en_addr_list), GFP_ATOMIC);
	if (tmp == NULL) {
		en_err(priv, "Failed to allocate address list\n");
		return (0);
	}
	memcpy(tmp->addr, LLADDR(sdl), ETH_ALEN);
	list_add_tail(&tmp->list, &priv->uc_list);

	return (1);
}