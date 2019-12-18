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
struct executable {int /*<<< orphan*/  x_signature_len; int /*<<< orphan*/  x_signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  receive_chunk (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
receive_signature(struct executable *x, int pipefd)
{

	receive_chunk(&x->x_signature, &x->x_signature_len, pipefd);
}