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
struct TYPE_2__ {int /*<<< orphan*/  m_snd_tag; } ;
struct mlx5e_channel {int /*<<< orphan*/  completion; TYPE_1__ tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_snd_tag_rele (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5e_chan_wait_for_completion(struct mlx5e_channel *c)
{

	m_snd_tag_rele(&c->tag.m_snd_tag);
	wait_for_completion(&c->completion);
}