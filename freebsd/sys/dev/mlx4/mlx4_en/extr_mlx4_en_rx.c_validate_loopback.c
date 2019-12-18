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
struct mlx4_en_priv {int loopback_ok; } ;
struct mbuf {unsigned char* m_data; } ;

/* Variables and functions */
 int ETHER_HDR_LEN ; 
 int MLX4_LOOPBACK_TEST_PAYLOAD ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void validate_loopback(struct mlx4_en_priv *priv, struct mbuf *mb)
{
	int i;
	int offset = ETHER_HDR_LEN;

	for (i = 0; i < MLX4_LOOPBACK_TEST_PAYLOAD; i++, offset++) {
		if (*(mb->m_data + offset) != (unsigned char) (i & 0xff))
			goto out_loopback;
	}
	/* Loopback found */
	priv->loopback_ok = 1;

out_loopback:
	m_freem(mb);
}