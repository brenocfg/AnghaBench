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
struct socket {int /*<<< orphan*/  so_snd; } ;
struct knote {int /*<<< orphan*/  kn_data; TYPE_1__* kn_fp; } ;
struct TYPE_2__ {struct socket* f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKBUF_LOCK_ASSERT (int /*<<< orphan*/ *) ; 
 scalar_t__ SOLISTENING (struct socket*) ; 
 int /*<<< orphan*/  sbused (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
filt_soempty(struct knote *kn, long hint)
{
	struct socket *so;

	so = kn->kn_fp->f_data;

	if (SOLISTENING(so))
		return (1);

	SOCKBUF_LOCK_ASSERT(&so->so_snd);
	kn->kn_data = sbused(&so->so_snd);

	if (kn->kn_data == 0)
		return (1);
	else
		return (0);
}