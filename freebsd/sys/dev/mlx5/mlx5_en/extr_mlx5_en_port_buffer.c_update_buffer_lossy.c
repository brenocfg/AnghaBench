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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_priv {int dummy; } ;
struct mlx5e_port_buffer {TYPE_1__* buffer; } ;
struct TYPE_2__ {int lossy; } ;

/* Variables and functions */
 int MLX5E_MAX_BUFFER ; 
 int MLX5E_MAX_PRIORITY ; 
 int update_xoff_threshold (struct mlx5e_priv*,struct mlx5e_port_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_buffer_lossy(struct mlx5e_priv *priv, unsigned int mtu,
			       u8 pfc_en, u8 *buffer, u32 xoff,
			       struct mlx5e_port_buffer *port_buffer,
			       bool *change)
{
	bool changed = false;
	u8 lossy_count;
	u8 prio_count;
	u8 lossy;
	int prio;
	int err;
	int i;

	for (i = 0; i < MLX5E_MAX_BUFFER; i++) {
		prio_count = 0;
		lossy_count = 0;

		for (prio = 0; prio < MLX5E_MAX_PRIORITY; prio++) {
			if (buffer[prio] != i)
				continue;

			prio_count++;
			lossy_count += !(pfc_en & (1 << prio));
		}

		if (lossy_count == prio_count)
			lossy = 1;
		else /* lossy_count < prio_count */
			lossy = 0;

		if (lossy != port_buffer->buffer[i].lossy) {
			port_buffer->buffer[i].lossy = lossy;
			changed = true;
		}
	}

	if (changed) {
		err = update_xoff_threshold(priv, port_buffer, xoff);
		if (err)
			return err;

		*change = true;
	}

	return 0;
}