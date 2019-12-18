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
struct TYPE_2__ {int /*<<< orphan*/  ext_arg1; } ;
struct mbuf {TYPE_1__ m_ext; } ;

/* Variables and functions */
 void ndis_return_packet (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ndis_ext_free(struct mbuf *m)
{

	return (ndis_return_packet(m->m_ext.ext_arg1));
}